#include "tree/icptree/sa/ChangeCorner0PositionRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

ChangeCorner0PositionRandomly::ChangeCorner0PositionRandomly() {

}

ChangeCorner0PositionRandomly::~ChangeCorner0PositionRandomly() {

}

void ChangeCorner0PositionRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->changeCorner0PositionRandomly();
    icpTree->placeMacrosAssumingNoSwitch();
}
