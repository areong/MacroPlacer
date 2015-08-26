#include "tree/icptree/sa/BoundingBoxArea.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

BoundingBoxArea::BoundingBoxArea() {

}

BoundingBoxArea::~BoundingBoxArea() {

}

double BoundingBoxArea::calculateCost(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    return floorplanState->getICPTree()->getBoundingBoxArea();
}
