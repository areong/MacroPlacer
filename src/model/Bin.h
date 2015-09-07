#ifndef MODEL_BIN_H_
#define MODEL_BIN_H_

#include <vector>

class Macro;

class Bin {
public:
    Bin(double xStart, double yStart, double xEnd, double yEnd);
    ~Bin();
    void addPreplacedMacro(Macro *macro);
    std::vector<Macro *> *getPreplacedMacros();
    void addMovableMacro(Macro *macro);
    std::vector<Macro *> *getMovableMacros();
    void clearMovableMacros();
    double getXStart();
    double getYStart();
    double getXEnd();
    double getYEnd();
    
private:
    double xStart;
    double xEnd;
    double yStart;
    double yEnd;
    std::vector<Macro *> *preplacedMacros;
    std::vector<Macro *> *movableMacros;
};

#endif