#ifndef TREE_ICPTREE_SA_CHANGECORNER0POSITIONRANDOMLY_H_
#define TREE_ICPTREE_SA_CHANGECORNER0POSITIONRANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class ChangeCorner0PositionRandomly : public Operation {
public:
    ChangeCorner0PositionRandomly();
    ~ChangeCorner0PositionRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif