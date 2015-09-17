#ifndef TREE_ICPTREE_SA_TOTALWIRELENGTH_H_
#define TREE_ICPTREE_SA_TOTALWIRELENGTH_H_

#include "sa/CostFunction.h"

/*
The State should be a FloorplanState.
The aspect ratio of bounding box.
*/
class TotalWirelength : public CostFunction {
public:
    /*
    @param targetRatio A positive double.
    */
    TotalWirelength();
    ~TotalWirelength();
    /*
    @Override
    */
    double calculateCost(State *state);

private:
    double targetRatio;
};

#endif