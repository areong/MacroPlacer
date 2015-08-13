#include "view/FloorplanWindow.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "model/Floorplan.h"
#include "view/FloorplanView.h"

FloorplanWindow *FloorplanWindow::floorplanWindow = 0;

void displayFunc() {
    FloorplanWindow::getInstance()->display();
}

FloorplanWindow *FloorplanWindow::createInstance(Floorplan *floorplan) {
    delete floorplanWindow;
    floorplanWindow = new FloorplanWindow(floorplan);
}

FloorplanWindow *FloorplanWindow::getInstance() {
    return floorplanWindow;
}

FloorplanWindow::~FloorplanWindow() {
    delete floorplanView;
}

void FloorplanWindow::setXYRangeByFloorplan() {
    setXYRange(floorplan->getMinX(), floorplan->getMaxX(), floorplan->getMinY(),
        floorplan->getMaxY());
}

void FloorplanWindow::display() {
    glutReshapeWindow(windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    floorplanView->display();
    glFlush();
}

void FloorplanWindow::setDisplayFunction() {
    glutDisplayFunc(displayFunc);
}

FloorplanWindow::FloorplanWindow(Floorplan *floorplan) {
    this->floorplan = floorplan;
    floorplanView = new FloorplanView(this, floorplan);
}
