#include "tree/icptree/sa/ChangeRandomMacroNodeVerticalDisplacementRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

ChangeRandomMacroNodeVerticalDisplacementRandomly::ChangeRandomMacroNodeVerticalDisplacementRandomly() {

}

ChangeRandomMacroNodeVerticalDisplacementRandomly::~ChangeRandomMacroNodeVerticalDisplacementRandomly() {

}

void ChangeRandomMacroNodeVerticalDisplacementRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->changeRandomMacroNodeVerticalDisplacementRandomly();
    icpTree->placeMacrosAssumingNoSwitch();
}
