#include "tree/icptree/sa/RemoveAndInsertRightNodeRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

RemoveAndInsertRightNodeRandomly::RemoveAndInsertRightNodeRandomly() {

}

RemoveAndInsertRightNodeRandomly::~RemoveAndInsertRightNodeRandomly() {

}

void RemoveAndInsertRightNodeRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->removeAndInsertRightNodeRandomly();
    icpTree->placeMacrosAssumingNoSwitch();
}
