#ifndef TREE_ICPTREE_SA_SWAPNODESRANDOMLY_H_
#define TREE_ICPTREE_SA_SWAPNODESRANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class SwapNodesRandomly : public Operation {
public:
    SwapNodesRandomly();
    ~SwapNodesRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif