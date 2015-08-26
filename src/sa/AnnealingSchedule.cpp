#include "sa/AnnealingSchedule.h"
#include <cmath>
#include "sa/CostFunction.h"
#include "sa/Operation.h"
#include "sa/SimulatedAnnealing.h"

AnnealingSchedule::AnnealingSchedule() {
    simulatedAnnealing = 0;
    initialTemperature = 0;
    temperature = 0;
}

AnnealingSchedule::~AnnealingSchedule() {

}

void AnnealingSchedule::setSimulatedAnnealing(SimulatedAnnealing *simulatedAnnealing) {
    this->simulatedAnnealing = simulatedAnnealing;
}

void AnnealingSchedule::initializeTemperature(State *state, int numMoves, double initialAcceptance) {
    CostFunction *costFunction = simulatedAnnealing->getCostFunction();
    Operation *operation = simulatedAnnealing->getOperation();
    double averagePositiveCostChange = 0;
    double previousCost = costFunction->calculateCost(state);
    int countPositiveCostChange = 0;
    for (int iMove = 0; iMove < numMoves; iMove++) {
        operation->operate(state);
        double currentCost = costFunction->calculateCost(state);
        double costChange = currentCost - previousCost;
        if (costChange > 0) {
            averagePositiveCostChange += costChange;
            countPositiveCostChange += 1;
        }
        previousCost = currentCost;
    }
    if (countPositiveCostChange > 0) {
        averagePositiveCostChange /= countPositiveCostChange;
    }
    initialTemperature = -1 * averagePositiveCostChange / log(initialAcceptance);
    temperature = initialTemperature;
}

double AnnealingSchedule::getTemperature() {
    return temperature;
}
