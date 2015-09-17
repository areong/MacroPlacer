#include "tree/icptree/sa/TotalWirelength.h"
#include "model/Floorplan.h"
#include "tree/icptree/sa/FloorplanState.h"

TotalWirelength::TotalWirelength() {

}

TotalWirelength::~TotalWirelength() {

}

double TotalWirelength::calculateCost(State *state) {
    FloorplanState *floorplanState = dynamic_cast<FloorplanState *>(state);
    return floorplanState->getFloorplan()->calculateNetsRoutabilityHpwl();
}
