#ifndef SA_COSTFUNCTIONGROUP_H_
#define SA_COSTFUNCTIONGROUP_H_

#include "sa/CostFunction.h"
#include <vector>

class Operation;

class CostFunctionGroup : public CostFunction {
public:
    CostFunctionGroup();
    /*
    Delete the vectors but not delete the CostFunctions.
    Because a CostFunction can belong to many CostFunctionGroups,
    doing so will cause double deletion, which should be avoided.
    */
    ~CostFunctionGroup();
    /*
    @param weight Value <= 0 is regarded as zero.
    */
    void addCostFunction(CostFunction *costFunction, double weight = 1);
    /*
    @param weight Value <= 0 is regarded as zero.
    */
    void setWeight(int ith, double weight);
    
    /*
    For all positive weights, normalize the weights such that their sum is one.
    */
    void normalizeWeights();
    /*
    Calculate the average cost of each CostFunction, which will divide the cost
    of each CostFunction in calculateCost() such that the values of all
    CostFunctions are about the same magnitude, i.e. normalized.
    Call it after setting Operation of SimulatedAnnealing and 
    setSimulatedAnnealing().
    @param numMoves The number of times to perform the operation to average the cost
                    of each CostFunction. numMoves should be > 0.
    */
    void normalizeCosts(State *state, Operation *operation, int numMoves);
    /*
    @Override
    cost = sum (weight_i * cost_i / averageCost_i)
    */
    double calculateCost(State *state);

private:
    std::vector<CostFunction *> *costFunctions;
    std::vector<double> *weights;
    std::vector<double> *averageCosts;
};

#endif