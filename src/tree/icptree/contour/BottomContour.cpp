#include "tree/icptree/contour/BottomContour.h"
#include "model/Macro.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/contour/Edge.h"

/*
Convert from TopContour to BottomContour:
    xStart -> xEnd
    xEnd -> xStart
    yStart -> yEnd
    yEnd -> yStart
*/

BottomContour::BottomContour() {

}

BottomContour::~BottomContour() {

}

void BottomContour::initializeHeadAndTail(int originX, int originY) {
    head = Edge::createBottomEdge(1e8, originX, originY);
    tail = Edge::createBottomEdge(originX, -1e8, originY);
}

int BottomContour::getOriginX() {
    return originX;
}

int BottomContour::getOriginY() {
    return originY;
}

void BottomContour::setMacroXStart(Macro *macro, int xStart) {
    macro->setXEnd(xStart);
}

void BottomContour::setMacroXEnd(Macro *macro, int xEnd) {
    macro->setXStart(xEnd);
}

void BottomContour::setMacroYStart(Macro *macro, int yStart) {
    macro->setYEnd(yStart);
}

void BottomContour::setMacroYEnd(Macro *macro, int yEnd) {
    macro->setYStart(yEnd);
}

int BottomContour::getMacroXStart(Macro *macro) {
    return macro->getXEnd();
}

int BottomContour::getMacroXEnd(Macro *macro) {
    return macro->getXStart();
}

int BottomContour::getMacroYStart(Macro *macro) {
    return macro->getYEnd();
}

int BottomContour::getMacroYEnd(Macro *macro) {
    return macro->getYStart();
}

int BottomContour::getMacroWidth(Macro *macro) {
    return macro->getWidth();
}

int BottomContour::getMacroHeight(Macro *macro) {
    return macro->getHeight();
}

Edge *BottomContour::createTopEdge(int xStart, int xEnd, int y) {
    return Edge::createBottomEdge(xStart, xEnd, y);
}

Edge *BottomContour::createMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->createBottomEdge();
}

Edge *BottomContour::getMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->getBottomEdge();
}

Edge *BottomContour::getMacroNodeBottomEdge(MacroNode *macroNode) {
    return macroNode->getTopEdge();
}

void BottomContour::setEdgeXStart(Edge *edge, int xStart) {
    edge->setXEnd(xStart);
}

void BottomContour::setEdgeXEnd(Edge *edge, int xEnd) {
    edge->setXStart(xEnd);
}

void BottomContour::setEdgeYStart(Edge *edge, int yStart) {
    edge->setYEnd(yStart);
}

void BottomContour::setEdgeYEnd(Edge *edge, int yEnd) {
    edge->setYStart(yEnd);
}

int BottomContour::getEdgeXStart(Edge *edge) {
    return edge->getXEnd();
}

int BottomContour::getEdgeXEnd(Edge *edge) {
    return edge->getXStart();
}

int BottomContour::getEdgeYStart(Edge *edge) {
    return edge->getYEnd();
}

int BottomContour::getEdgeYEnd(Edge *edge) {
    return edge->getYStart();
}

void BottomContour::initializeLocalMaxY() {
    localMaxY = 1e8;
}

void BottomContour::addToLocalMaxY(int value) {
    localMaxY -= value;
}

void BottomContour::initializeMaxMinXY() {
    maxX = 1e8;
    minX = -1e8;
    maxY = 1e8;
    minY = -1e8;
}

bool BottomContour::isX1Larger(int x1, int x2) {
    return x1 < x2;
}

bool BottomContour::isX1NotSmaller(int x1, int x2) {
    return x1 <= x2;
}

bool BottomContour::isX1Smaller(int x1, int x2) {
    return x1 > x2;
}

bool BottomContour::isX1NotLarger(int x1, int x2) {
    return x1 >= x2;
}

bool BottomContour::isY1Larger(int y1, int y2) {
    return y1 < y2;
}

bool BottomContour::isY1NotSmaller(int y1, int y2) {
    return y1 <= y2;
}

bool BottomContour::isY1Smaller(int y1, int y2) {
    return y1 > y2;
}

bool BottomContour::isY1NotLarger(int y1, int y2) {
    return y1 >= y2;
}

int BottomContour::getYDifference(int y1, int y2) {
    return y2 - y1;
}

int BottomContour::addToX(int x, int value) {
    return x - value;
}

int BottomContour::addToY(int y, int value) {
    return y - value;
}