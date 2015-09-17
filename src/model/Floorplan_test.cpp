#include "model/Floorplan_test.h"
#include <iostream>
#include <vector>
#include "model/Bin.h"
#include "model/Cell.h"
#include "model/Floorplan.h"
#include "model/Macro.h"
#include "model/Terminal.h"
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

void testFloorplan_readAux(int argc, char **argv) {
    if (argc < 2) {
        return;
    }
    Floorplan *floorplan = Floorplan::createFromAuxFiles(argv[1]);
    std::cout << floorplan->getPreplacedMacros()->size() << ", "
              << floorplan->getMovableMacros()->size() << ", "
              << floorplan->getCells()->size() << ", "
              << floorplan->getTerminals()->size() << ", "
              << floorplan->getNets()->size() << "\n";

    int countNonAtZeroTerminals = 0;
    for (int i = 0; i < floorplan->getTerminals()->size(); ++i) {
        if (floorplan->getTerminals()->at(i)->getX() != 0 &&
            floorplan->getTerminals()->at(i)->getY() != 0) {
            countNonAtZeroTerminals += 1;
        }
    }
    std::cout << countNonAtZeroTerminals << "\n";

    int countPins = 0;
    for (int i = 0; i < floorplan->getPreplacedMacros()->size(); ++i) {
        countPins += floorplan->getPreplacedMacros()->at(i)->getPins()->size();
    }
    for (int i = 0; i < floorplan->getMovableMacros()->size(); ++i) {
        countPins += floorplan->getMovableMacros()->at(i)->getPins()->size();
    }
    for (int i = 0; i < floorplan->getCells()->size(); ++i) {
        countPins += floorplan->getCells()->at(i)->getPins()->size();
    }
    for (int i = 0; i < floorplan->getTerminals()->size(); ++i) {
        countPins += floorplan->getTerminals()->at(i)->getPins()->size();
    }
    std::cout << countPins << "\n";

    delete floorplan;
}

void testFloorplan(int argc, char **argv) {
    //testFloorplan_addMacrosToBins();
    testFloorplan_readAux(argc, argv);
}
