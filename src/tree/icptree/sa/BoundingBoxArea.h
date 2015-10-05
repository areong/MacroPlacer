#ifndef TREE_ICPTREE_SA_BOUNDINGBOXAREA_H_
#define TREE_ICPTREE_SA_BOUNDINGBOXAREA_H_

#include "sa/CostFunction.h"

/*
The State should be a FloorplanState.
*/
class BoundingBoxArea : public CostFunction {
public:
    BoundingBoxArea(int targetArea);
    ~BoundingBoxArea();
    /*
    @Override
    */
    double calculateCost(State *state);

private:
    int targetArea;
};

#endif