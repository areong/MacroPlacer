#include "model/sa/CountOfMovableMacrosOutsideDesiredRegion.h"
#include "model/Floorplan.h"
#include "model/sa/FloorplanState.h"

CountOfMovableMacrosOutsideDesiredRegion::CountOfMovableMacrosOutsideDesiredRegion() {

}

CountOfMovableMacrosOutsideDesiredRegion::~CountOfMovableMacrosOutsideDesiredRegion() {

}

double CountOfMovableMacrosOutsideDesiredRegion::calculateCost(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    return floorplanState->getFloorplan()->countMovableMacrosOutsideDesiredRegion();
}
