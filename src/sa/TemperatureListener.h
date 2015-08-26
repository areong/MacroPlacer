#ifndef SA_TEMPERATURELISTENER_H_
#define SA_TEMPERATURELISTENER_H_

class SimulatedAnnealing;

class TemperatureListener {
public:
    TemperatureListener();
    ~TemperatureListener();
    void setSimulatedAnnealing(SimulatedAnnealing *simulatedAnnealing);
    /*
    Called when the temperature updates.
    */
    virtual void onUpdate() = 0;

protected:
    SimulatedAnnealing *simulatedAnnealing;
};

#endif