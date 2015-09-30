#include "tree/icptree/sa/ChangeRandomMacroNodeSpacingRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

ChangeRandomMacroNodeSpacingRandomly::ChangeRandomMacroNodeSpacingRandomly() {

}

ChangeRandomMacroNodeSpacingRandomly::~ChangeRandomMacroNodeSpacingRandomly() {

}

void ChangeRandomMacroNodeSpacingRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->changeRandomMacroNodeSpacingRandomly();
}
