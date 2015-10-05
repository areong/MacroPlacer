#include "tree/icptree/sa/RefreshWindow.h"
#include "model/Floorplan.h"
#include "model/sa/FloorplanState.h"
#include "tree/icptree/ICPTree.h"
#include "sa/SimulatedAnnealing.h"
#include "view/Window.h"

RefreshWindow::RefreshWindow(Window *window, Floorplan *floorplan) {
    this->window = window;
    this->floorplan = floorplan;
}

RefreshWindow::~RefreshWindow() {

}

void RefreshWindow::onUpdate() {
    FloorplanState *bestFloorplanState = dynamic_cast<FloorplanState *>(simulatedAnnealing->getBestState());
    ICPTree *bestICPTree = bestFloorplanState->getICPTree();
    bestICPTree->placeMacrosAssumingNoSwitch();
    floorplan->clearBinsMovableMacros();
    floorplan->addMovableMacrosToBins();
    floorplan->setICPTree(bestICPTree);
    window->runMainLoopEvent();
}
