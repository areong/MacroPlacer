#include "tree/icptree/sa/RemoveAndInsertLeftNodeRandomly.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"

RemoveAndInsertLeftNodeRandomly::RemoveAndInsertLeftNodeRandomly() {

}

RemoveAndInsertLeftNodeRandomly::~RemoveAndInsertLeftNodeRandomly() {

}

void RemoveAndInsertLeftNodeRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->removeAndInsertLeftNodeRandomly();
}
