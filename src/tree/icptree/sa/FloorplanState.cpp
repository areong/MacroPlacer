#include "tree/icptree/sa/FloorplanState.h"
#include "model/Floorplan.h"
#include "tree/icptree/ICPTree.h"

FloorplanState::FloorplanState(Floorplan *floorplan) {
    this->floorplan = floorplan;
    this->icpTree = floorplan->getICPTree();
}

FloorplanState::FloorplanState(Floorplan *floorplan, ICPTree *icpTree) {
    this->floorplan = floorplan;
    this->icpTree = icpTree;
}

FloorplanState::~FloorplanState() {
    delete icpTree;
}

void FloorplanState::setFloorplan(Floorplan *floorplan) {
    this->floorplan = floorplan;
}

Floorplan *FloorplanState::getFloorplan() {
    return floorplan;
}

void FloorplanState::setICPTree(ICPTree *icpTree) {
    this->icpTree = floorplan->getICPTree();
}

ICPTree *FloorplanState::getICPTree() {
    return icpTree;
}

State *FloorplanState::copy() {
    return new FloorplanState(floorplan, dynamic_cast<ICPTree *>(icpTree->copy()));
}
