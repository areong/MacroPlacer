#include "tree/icptree/sa/BoundingBoxArea.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

BoundingBoxArea::BoundingBoxArea(int targetArea) {
    this->targetArea = targetArea;
}

BoundingBoxArea::~BoundingBoxArea() {

}

double BoundingBoxArea::calculateCost(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    int boundingBoxArea = floorplanState->getICPTree()->getBoundingBoxArea();
    if (boundingBoxArea > targetArea) {
        return boundingBoxArea - targetArea;
    } else {
        return targetArea - boundingBoxArea;
    }
}
