#include "sa/CostFunctionGroup.h"
#include "sa/Operation.h"
#include "sa/State.h"

CostFunctionGroup::CostFunctionGroup() {
    costFunctions = new std::vector<CostFunction *>();
    weights = new std::vector<double>();
    averageCosts = new std::vector<double>();
}

CostFunctionGroup::~CostFunctionGroup() {
    delete costFunctions;
    delete weights;
    delete averageCosts;
}

void CostFunctionGroup::addCostFunction(CostFunction *costFunction, double weight) {
    costFunctions->push_back(costFunction);
    if (weight < 0) {
        weight = 0;
    }
    weights->push_back(weight);
    averageCosts->push_back(1);
}

void CostFunctionGroup::setWeight(int ith, double weight) {
    if (weight < 0) {
        weight = 0;
    }
    weights->at(ith) = weight;
}

void CostFunctionGroup::normalizeWeights() {
    double sumWeights = 0;
    for (int i = 0; i < weights->size(); i++) {
        if (weights->at(i) <= 0) {
            continue;
        }
        sumWeights += weights->at(i);
    }
    if (sumWeights > 0) {
        for (int i = 0; i < weights->size(); i++) {
            weights->at(i) /= sumWeights;
        }
    }
}

void CostFunctionGroup::normalizeCosts(State *state, Operation *operation, int numMoves) {
    // Assign the averageCosts as the initial cost.
    state->doBeforeCalculatingCost();
    for (int i = 0; i < averageCosts->size(); i++) {
        averageCosts->at(i) = costFunctions->at(i)->calculateCost(state);
    }
    // Calculate the average cost of each CostFunction.
    for (int iMove = 0; iMove < numMoves; iMove++) {
        operation->operate(state);
        state->doAfterBeingOperated();
        state->doBeforeCalculatingCost();
        for (int i = 0; i < averageCosts->size(); i++) {
            averageCosts->at(i) += costFunctions->at(i)->calculateCost(state);
        }
    }
    // Calculate the averageCosts such that the sum is one.
    for (int i = 0; i < averageCosts->size(); i++) {
        averageCosts->at(i) /= numMoves + 1;
    }
}

double CostFunctionGroup::calculateCost(State *state) {
    double cost = 0;
    for (int i = 0; i < costFunctions->size(); i++) {
        cost += weights->at(i) * costFunctions->at(i)->calculateCost(state) / averageCosts->at(i);
    }
    return cost;
}
