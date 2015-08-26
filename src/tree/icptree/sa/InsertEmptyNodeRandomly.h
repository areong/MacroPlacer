#ifndef TREE_ICPTREE_SA_INSERTEMPTYNODERANDOMLY_H_
#define TREE_ICPTREE_SA_INSERTEMPTYNODERANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class InsertEmptyNodeRandomly : public Operation {
public:
    InsertEmptyNodeRandomly();
    ~InsertEmptyNodeRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif