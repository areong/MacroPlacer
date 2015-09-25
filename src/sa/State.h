#ifndef SA_STATE_H_
#define SA_STATE_H_

class State {
public:
    virtual ~State() {}
    /*
    Called each time after the State is operated by some Operation in
        CostFunctionGroup.normalizeCosts(),
        AnnealingSchedule.initializeTemperature(), and
        SimulatedAnnealing.anneal().
    */
    virtual void doAfterBeingOperated() = 0;
    /*
    Called each time before some CostFunction is going to calculate
    the cost of the State in
        CostFunctionGroup.normalizeCosts(),
        AnnealingSchedule.initializeTemperature(), and
        SimulatedAnnealing.anneal().
    */
    virtual void doBeforeCalculatingCost() = 0;
    virtual State *copy() = 0;
};

#endif