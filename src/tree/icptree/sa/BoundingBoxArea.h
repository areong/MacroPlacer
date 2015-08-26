#ifndef TREE_ICPTREE_SA_BOUNDINGBOXAREA_H_
#define TREE_ICPTREE_SA_BOUNDINGBOXAREA_H_

#include "sa/CostFunction.h"

/*
The State should be a FloorplanState.
*/
class BoundingBoxArea : public CostFunction {
public:
    BoundingBoxArea();
    ~BoundingBoxArea();
    /*
    @Override
    */
    double calculateCost(State *state);
};

#endif