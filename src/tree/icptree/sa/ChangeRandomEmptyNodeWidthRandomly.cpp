#include "tree/icptree/sa/ChangeRandomEmptyNodeWidthRandomly.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"

ChangeRandomEmptyNodeWidthRandomly::ChangeRandomEmptyNodeWidthRandomly() {

}

ChangeRandomEmptyNodeWidthRandomly::~ChangeRandomEmptyNodeWidthRandomly() {

}

void ChangeRandomEmptyNodeWidthRandomly::operate(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    ICPTree *icpTree = floorplanState->getICPTree();
    icpTree->changeRandomEmptyNodeWidthRandomly();
}
