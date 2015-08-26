#ifndef TREE_ICPTREE_SA_CHANGERANDOMEMPTYNODEWIDTHRANDOMLY_H_
#define TREE_ICPTREE_SA_CHANGERANDOMEMPTYNODEWIDTHRANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class ChangeRandomEmptyNodeWidthRandomly : public Operation {
public:
    ChangeRandomEmptyNodeWidthRandomly();
    ~ChangeRandomEmptyNodeWidthRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif