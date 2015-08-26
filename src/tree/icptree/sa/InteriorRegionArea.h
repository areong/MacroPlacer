#ifndef TREE_ICPTREE_SA_INTERIORREGIONAREA_H_
#define TREE_ICPTREE_SA_INTERIORREGIONAREA_H_

#include "sa/CostFunction.h"

/*
The State should be a FloorplanState.
*/
class InteriorRegionArea : public CostFunction {
public:
    InteriorRegionArea(int targetArea);
    ~InteriorRegionArea();
    /*
    @Override
    */
    double calculateCost(State *state);

private:
    int targetArea;
};

#endif