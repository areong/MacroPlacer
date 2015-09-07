#ifndef MODEL_NET_H_
#define MODEL_NET_H_

#include <string>
#include <vector>

class Floorplan;
class Pin;

class Net {
public:
    Net(Floorplan *floorplan, std::string name);
    /*
    Does not delete the Pins, which will be deleted when the Modules are deleted.
    */
    ~Net();
    std::string getName();
    void addMacroPin(Pin *pin);
    void addCellPin(Pin *pin);
    void addTerminalPin(Pin *pin);
    double calculateHPWL();
    double calculateRoutabilityHPWL();

private:
    Floorplan *floorplan;
    std::string name;
    std::vector<Pin *> *macroPins;
    std::vector<Pin *> *cellPins;
    std::vector<Pin *> *terminalPins;

    double minPinsX;
    double minPinsY;
    double maxPinsX;
    double maxPinsY;
};

#endif