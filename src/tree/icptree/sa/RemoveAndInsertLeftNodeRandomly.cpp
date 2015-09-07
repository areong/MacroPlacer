#include "tree/icptree/sa/RemoveAndInsertLeftNodeRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

RemoveAndInsertLeftNodeRandomly::RemoveAndInsertLeftNodeRandomly() {

}

RemoveAndInsertLeftNodeRandomly::~RemoveAndInsertLeftNodeRandomly() {

}

void RemoveAndInsertLeftNodeRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->removeAndInsertLeftNodeRandomly();
}
