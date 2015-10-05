#include "tree/icptree/sa/RemoveAndInsertRightNodeRandomly.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"

RemoveAndInsertRightNodeRandomly::RemoveAndInsertRightNodeRandomly() {

}

RemoveAndInsertRightNodeRandomly::~RemoveAndInsertRightNodeRandomly() {

}

void RemoveAndInsertRightNodeRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->removeAndInsertRightNodeRandomly();
}
