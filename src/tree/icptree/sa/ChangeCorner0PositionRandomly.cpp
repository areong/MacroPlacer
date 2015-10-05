#include "tree/icptree/sa/ChangeCorner0PositionRandomly.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"

ChangeCorner0PositionRandomly::ChangeCorner0PositionRandomly() {

}

ChangeCorner0PositionRandomly::~ChangeCorner0PositionRandomly() {

}

void ChangeCorner0PositionRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->changeCorner0PositionRandomly();
}
