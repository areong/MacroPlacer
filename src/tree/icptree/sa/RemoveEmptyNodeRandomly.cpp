#include "tree/icptree/sa/RemoveEmptyNodeRandomly.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"

RemoveEmptyNodeRandomly::RemoveEmptyNodeRandomly() {

}

RemoveEmptyNodeRandomly::~RemoveEmptyNodeRandomly() {

}

void RemoveEmptyNodeRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->removeEmptyNodeRandomly();
}
