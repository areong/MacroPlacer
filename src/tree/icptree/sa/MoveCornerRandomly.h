#ifndef TREE_ICPTREE_SA_MOVECORNERRANDOMLY_H_
#define TREE_ICPTREE_SA_MOVECORNERRANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class MoveCornerRandomly : public Operation {
public:
    MoveCornerRandomly();
    ~MoveCornerRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif