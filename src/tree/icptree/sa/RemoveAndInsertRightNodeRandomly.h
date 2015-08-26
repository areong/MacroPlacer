#ifndef TREE_ICPTREE_SA_REMOVEANDINSERTRIGHTNODERANDOMLY_H_
#define TREE_ICPTREE_SA_REMOVEANDINSERTRIGHTNODERANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class RemoveAndInsertRightNodeRandomly : public Operation {
public:
    RemoveAndInsertRightNodeRandomly();
    ~RemoveAndInsertRightNodeRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif