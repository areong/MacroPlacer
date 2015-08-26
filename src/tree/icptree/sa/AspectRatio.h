#ifndef TREE_ICPTREE_SA_ASPECTRATIO_H_
#define TREE_ICPTREE_SA_ASPECTRATIO_H_

#include "sa/CostFunction.h"

/*
The State should be a FloorplanState.
The aspect ratio of bounding box.
*/
class AspectRatio : public CostFunction {
public:
    /*
    @param targetRatio A positive double.
    */
    AspectRatio(double targetRatio);
    ~AspectRatio();
    /*
    @Override
    */
    double calculateCost(State *state);

private:
    double targetRatio;
};

#endif