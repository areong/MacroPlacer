#ifndef TREE_ICPTREE_SA_REMOVEEMPTYNODERANDOMLY_H_
#define TREE_ICPTREE_SA_REMOVEEMPTYNODERANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class RemoveEmptyNodeRandomly : public Operation {
public:
    RemoveEmptyNodeRandomly();
    ~RemoveEmptyNodeRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif