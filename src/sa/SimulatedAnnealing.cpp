#include "sa/SimulatedAnnealing.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include "sa/AnnealingSchedule.h"
#include "sa/CostFunction.h"
#include "sa/Operation.h"
#include "sa/State.h"
#include "sa/TemperatureListener.h"
#include "utils/Utils.h"

SimulatedAnnealing::SimulatedAnnealing() {
    costFunction = 0;
    operation = 0;
    annealingSchedule = 0;
    temperatureListeners = new std::vector<TemperatureListener *>();
    averageCostChange = 0;
    bestState = 0;
    timeStart = 0;
    timeLimit = 0;
}

SimulatedAnnealing::~SimulatedAnnealing() {
    delete temperatureListeners;
}

void SimulatedAnnealing::setOperation(Operation *operation) {
    this->operation = operation;
}

Operation *SimulatedAnnealing::getOperation() {
    return operation;
}

void SimulatedAnnealing::setCostFunction(CostFunction *costFunction) {
    this->costFunction = costFunction;
}

CostFunction *SimulatedAnnealing::getCostFunction() {
    return costFunction;
}

void SimulatedAnnealing::setAnnealingSchedule(AnnealingSchedule *annealingSchedule) {
    this->annealingSchedule = annealingSchedule;
    annealingSchedule->setSimulatedAnnealing(this);
}

void SimulatedAnnealing::addTemperatureListener(TemperatureListener *temperatureListener) {
    temperatureListeners->push_back(temperatureListener);
    temperatureListener->setSimulatedAnnealing(this);
}

void SimulatedAnnealing::anneal(State *state, int numMovesPerTemperature, double lowestTemperature, double highestRejectionRatio, double timeLimit) {
    // Assume the temperature is initialized beforehand.
    startTiming(timeLimit);
    if (bestState != 0) {
        delete bestState;
    }
    bestState = state;
    double lowestCost = 1e8;
    state->doBeforeCalculatingCost();
    double previousCost = costFunction->calculateCost(state);
    while (true) {
        int countRejection = 0;
        averageCostChange = 0;
        for (int iMove = 0; iMove < numMovesPerTemperature; iMove++) {
            State *newState = state->copy();
            operation->operate(newState);
            newState->doAfterBeingOperated();
            newState->doBeforeCalculatingCost();
            double newCost = costFunction->calculateCost(newState);
            double costChange = newCost - previousCost;
            averageCostChange += costChange;
            if (costChange <= 0 || Utils::random() < exp(-1 * costChange / annealingSchedule->getTemperature())) {
                if (newCost < lowestCost) {
                    bestState = newState;
                    lowestCost = newCost;
                    delete state;
                } else if (bestState != state) {
                    delete state;
                }
                state = newState;
            } else {
                delete newState;
                countRejection += 1;
            }
        }
        averageCostChange /= numMovesPerTemperature;
        annealingSchedule->updateTemperature();
        // Call listeners.
        for (int i = 0; i < temperatureListeners->size(); i++) {
            temperatureListeners->at(i)->onUpdate();
        }
        //std::cout << "rejectionRatio: " << (double) countRejection / (double) numMovesPerTemperature << "\n";
        // Termination conditions
        if ((double) countRejection / (double) numMovesPerTemperature > highestRejectionRatio ||
            annealingSchedule->getTemperature() < lowestTemperature ||
            isOutOfTime()) {
            break;
        }
    }
}

double SimulatedAnnealing::getAverageCostChange() {
    return averageCostChange;
}

State *SimulatedAnnealing::getBestState() {
    return bestState;
}

// Private

void SimulatedAnnealing::startTiming(double timeLimit) {
    timeStart = clock();
    this->timeLimit = timeLimit * CLOCKS_PER_SEC;
}

bool SimulatedAnnealing::isOutOfTime() {
    return clock() - timeStart > timeLimit;
}

