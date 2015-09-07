#include "tree/icptree/sa/SwapNodesRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

SwapNodesRandomly::SwapNodesRandomly() {

}

SwapNodesRandomly::~SwapNodesRandomly() {

}

void SwapNodesRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->swapNodesRandomly();
}
