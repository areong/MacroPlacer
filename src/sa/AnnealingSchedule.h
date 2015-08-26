#ifndef SA_ANNEALINGSCHEDULE_H_
#define SA_ANNEALINGSCHEDULE_H_

class SimulatedAnnealing;
class State;

class AnnealingSchedule {
public:
    AnnealingSchedule();
    ~AnnealingSchedule();
    void setSimulatedAnnealing(SimulatedAnnealing *simulatedAnnealing);
    /*
    Initialize the temperature as -Δavg / lnP.
    Call it after setting Operation and CostFunction of SimulatedAnnealing
    and setSimulatedAnnealing().
    @param numMoves The number of operations done to get average positive cost change.
                    numMoves should > 0.
    @param initialAcceptance Initial acceptance probability. It should < 1.
    */
    void initializeTemperature(State *state, int numMoves, double initialAcceptance);
    double getTemperature();
    virtual void updateTemperature() = 0;

protected:
    SimulatedAnnealing *simulatedAnnealing;
    double initialTemperature;
    double temperature;
};

#endif