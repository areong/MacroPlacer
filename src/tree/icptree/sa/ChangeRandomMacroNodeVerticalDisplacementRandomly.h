#ifndef TREE_ICPTREE_SA_CHANGERANDOMMACRONODEVERTICALDISPLACEMENTRANDOMLY_H_
#define TREE_ICPTREE_SA_CHANGERANDOMMACRONODEVERTICALDISPLACEMENTRANDOMLY_H_

#include "sa/Operation.h"

/*
The State should be a FloorplanState.
*/
class ChangeRandomMacroNodeVerticalDisplacementRandomly : public Operation {
public:
    ChangeRandomMacroNodeVerticalDisplacementRandomly();
    ~ChangeRandomMacroNodeVerticalDisplacementRandomly();
    /*
    @Override
    Place macros after the operation.
    */
    void operate(State *state);
};

#endif