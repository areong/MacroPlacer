#include "sa/SimulatedAnnealing_test.h"
#include <iostream>
#include "sa/AnnealingScheduleRatioDecrease.h"
#include "sa/DecreaseVariable.h"
#include "sa/IncreaseVariable.h"
#include "sa/OperationSet.h"
#include "sa/Polynomial.h"
#include "sa/Variable.h"
#include "sa/SimulatedAnnealing.h"

void testSimulatedAnnealing_polynomial() {
    Variable *variable = new Variable(0);
    Polynomial *polynomial = new Polynomial(5, 2, -2, -0.5, 0.3);
    // Using steps of 0.001 finds the best variable easily,
    // while using steps of 0.0001 hardly finds one.
    // The distance of moves is also an important aspect of simulated annealing.
    IncreaseVariable *increaseVariable = new IncreaseVariable(0.001);
    DecreaseVariable *decreaseVariable = new DecreaseVariable(0.001);
    OperationSet *operationSet = new OperationSet();
    operationSet->addOperation(increaseVariable);
    operationSet->addOperation(decreaseVariable);
    AnnealingScheduleRatioDecrease *annealingScheduleRatioDecrease = new AnnealingScheduleRatioDecrease(0.9);
    SimulatedAnnealing *simulatedAnnealing = new SimulatedAnnealing();
    simulatedAnnealing->setOperation(operationSet);
    simulatedAnnealing->setCostFunction(polynomial);
    simulatedAnnealing->setAnnealingSchedule(annealingScheduleRatioDecrease);

    annealingScheduleRatioDecrease->initializeTemperature(variable, 1000, 0.85);
    std::cout << "initialTemperature: " << annealingScheduleRatioDecrease->getTemperature() << "\n";
    simulatedAnnealing->anneal(variable, 10000, 0.00001, 0.95, 60);
    Variable *bestVariable = dynamic_cast<Variable *>(simulatedAnnealing->getBestState());
    std::cout << "bestVariable: " << bestVariable->getValue() << "\n";
    std::cout << "polynomial value: " << polynomial->calculateCost(bestVariable) << "\n";
}

void testSimulatedAnnealing() {
    testSimulatedAnnealing_polynomial();
}