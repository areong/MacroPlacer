#ifndef MODEL_SA_MACROSDISPLACEMENT_H_
#define MODEL_SA_MACROSDISPLACEMENT_H_

#include "sa/CostFunction.h"

/*
The State should be a FloorplanState.
*/
class MacrosDisplacement : public CostFunction {
public:
    MacrosDisplacement();
    ~MacrosDisplacement();
    /*
    @Override
    */
    double calculateCost(State *state);
};

#endif