#include "view/FloorplanWindow_test.h"
#include "view/FloorplanWindow.h"

void testFloorplanWindow() {
    // Without a real Floorplan, this function will cause segmentation fault.
    FloorplanWindow *floorplanWindow = FloorplanWindow::createInstance(0);
    floorplanWindow->setWindowSize(250, 250);
    floorplanWindow->setXYRange(0, 250, 0, 250);
    floorplanWindow->initialize();
    floorplanWindow->runMainLoop();
}