#include "model/Floorplan_test.h"
#include <vector>
#include "model/Bin.h"
#include "model/Floorplan.h"
#include "model/Macro.h"
#include "utils/Utils.h"
#include "view/FloorplanWindow.h"

void testFloorplan_addMacrosToBins() {
    Floorplan *floorplan = new Floorplan();
    floorplan->createBins(0, 0, 1000, 1000, 100, 100);

    //// Add Macros to all Bins in a range.
    //std::vector<Bin *> *bins = floorplan->getBinsUnderRectangle(-10, 0, 1000, 2000);
    //for (int i = 0; i < bins->size(); ++i) {
    //    bins->at(i)->addMovableMacro(new Macro());
    //}

    // Scatter Macros in all Bins.
    for (int i = 0; i < 10; ++i) {
        Macro *macro = new Macro();
        macro->setXStart(Utils::randint(0, 1000));
        macro->setYStart(Utils::randint(0, 1000));
        floorplan->addMovableMacro(macro);
    }
    floorplan->clearBinsMovableMacros();
    floorplan->addMovableMacrosToBins();

    FloorplanWindow *window = FloorplanWindow::createInstance(floorplan);
    window->setWindowSize(1024, 768);
    window->setXYRangeByFloorplan();
    window->initialize();
    window->runMainLoop();
}

void testFloorplan() {
    testFloorplan_addMacrosToBins();
}
