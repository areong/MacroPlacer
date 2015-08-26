#include "tree/icptree/sa/RemoveEmptyNodeRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

RemoveEmptyNodeRandomly::RemoveEmptyNodeRandomly() {

}

RemoveEmptyNodeRandomly::~RemoveEmptyNodeRandomly() {

}

void RemoveEmptyNodeRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->removeEmptyNodeRandomly();
    icpTree->placeMacrosAssumingNoSwitch();
}
