#include "tree/icptree/sa/InteriorRegionArea.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/sa/FloorplanState.h"

InteriorRegionArea::InteriorRegionArea(int targetArea) {
    this->targetArea = targetArea;
}

InteriorRegionArea::~InteriorRegionArea() {

}

double InteriorRegionArea::calculateCost(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    int interiorRegionArea = floorplanState->getICPTree()->getInteriorRegionArea();
    if (interiorRegionArea < targetArea) {
        return targetArea - interiorRegionArea;
    } else {
        return interiorRegionArea - targetArea;
    }
}
