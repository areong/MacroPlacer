#ifndef TREE_ICPTREE_SA_REMOVEANDINSERTLEFTNODERANDOMLY_H_
#define TREE_ICPTREE_SA_REMOVEANDINSERTLEFTNODERANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class RemoveAndInsertLeftNodeRandomly : public Operation {
public:
    RemoveAndInsertLeftNodeRandomly();
    ~RemoveAndInsertLeftNodeRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif