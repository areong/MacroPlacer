#ifndef MODEL_SA_COUNTOFMOVABLEMACROSOUTSIDEDESIREDREGION_H_
#define MODEL_SA_COUNTOFMOVABLEMACROSOUTSIDEDESIREDREGION_H_

#include "sa/CostFunction.h"

/*
The State should be a FloorplanState.
*/
class CountOfMovableMacrosOutsideDesiredRegion : public CostFunction {
public:
    CountOfMovableMacrosOutsideDesiredRegion();
    ~CountOfMovableMacrosOutsideDesiredRegion();
    /*
    @Override
    */
    double calculateCost(State *state);
};

#endif