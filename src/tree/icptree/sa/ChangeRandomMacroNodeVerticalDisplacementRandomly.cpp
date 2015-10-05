#include "tree/icptree/sa/ChangeRandomMacroNodeVerticalDisplacementRandomly.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"

ChangeRandomMacroNodeVerticalDisplacementRandomly::ChangeRandomMacroNodeVerticalDisplacementRandomly() {

}

ChangeRandomMacroNodeVerticalDisplacementRandomly::~ChangeRandomMacroNodeVerticalDisplacementRandomly() {

}

void ChangeRandomMacroNodeVerticalDisplacementRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->changeRandomMacroNodeVerticalDisplacementRandomly();
}
