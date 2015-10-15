#include "model/sa/MacrosDisplacement.h"
#include "model/Floorplan.h"
#include "model/sa/FloorplanState.h"

MacrosDisplacement::MacrosDisplacement() {

}

MacrosDisplacement::~MacrosDisplacement() {

}

double MacrosDisplacement::calculateCost(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    return floorplanState->getFloorplan()->calculateMacrosDisplacement();
}
