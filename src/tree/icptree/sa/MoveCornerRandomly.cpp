#include "tree/icptree/sa/MoveCornerRandomly.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

MoveCornerRandomly::MoveCornerRandomly() {

}

MoveCornerRandomly::~MoveCornerRandomly() {

}

void MoveCornerRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->moveCornerRandomly();
}
