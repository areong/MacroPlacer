#ifndef SA_SIMULATEDANNEALING_H_
#define SA_SIMULATEDANNEALING_H_

#include <vector>

class AnnealingSchedule;
class CostFunction;
class Operation;
class State;
class TemperatureListener;

class SimulatedAnnealing {
public:
    SimulatedAnnealing();
    ~SimulatedAnnealing();
    void setOperation(Operation *operation);
    Operation *getOperation();
    void setCostFunction(CostFunction *costFunction);
    CostFunction *getCostFunction();
    void setAnnealingSchedule(AnnealingSchedule *annealingSchedule);
    /*
    TemperatureListeners are called when the temperature updates.
    */
    void addTemperatureListener(TemperatureListener *temperatureListener);
    /*
    Please call AnnealingSchedule.initializeTemperature() beforehand.
    @param numMovesPerTemperature It should be > 0.
    @param timeLimit Time limit in seconds.
    */
    void anneal(State *state, int numMovesPerTemperature, double lowestTemperature, double highestRejectionRatio, double timeLimit);
    double getAverageCostChange();
    State *getBestState();

private:
    Operation *operation;
    CostFunction *costFunction;
    AnnealingSchedule *annealingSchedule;
    std::vector<TemperatureListener *> *temperatureListeners;

    double averageCostChange;
    State *bestState;

    int timeStart;
    double timeLimit;
    void startTiming(double timeLimit);
    bool isOutOfTime();
};

#endif