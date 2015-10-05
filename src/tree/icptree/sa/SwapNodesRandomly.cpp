#include "tree/icptree/sa/SwapNodesRandomly.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"

SwapNodesRandomly::SwapNodesRandomly() {

}

SwapNodesRandomly::~SwapNodesRandomly() {

}

void SwapNodesRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->swapNodesRandomly();
}
