#include "tree/icptree/sa/ChangeRandomEmptyNodeWidthRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

ChangeRandomEmptyNodeWidthRandomly::ChangeRandomEmptyNodeWidthRandomly() {

}

ChangeRandomEmptyNodeWidthRandomly::~ChangeRandomEmptyNodeWidthRandomly() {

}

void ChangeRandomEmptyNodeWidthRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->changeRandomEmptyNodeWidthRandomly();
    icpTree->placeMacrosAssumingNoSwitch();
}
