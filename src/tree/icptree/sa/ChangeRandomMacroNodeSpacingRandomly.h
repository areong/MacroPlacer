#ifndef TREE_ICPTREE_SA_CHANGERANDOMMACRONODESPACINGRANDOMLY_H_
#define TREE_ICPTREE_SA_CHANGERANDOMMACRONODESPACINGRANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class ChangeRandomMacroNodeSpacingRandomly : public Operation {
public:
    ChangeRandomMacroNodeSpacingRandomly();
    ~ChangeRandomMacroNodeSpacingRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif