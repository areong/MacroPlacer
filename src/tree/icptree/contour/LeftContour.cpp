#include "tree/icptree/contour/LeftContour.h"
#include "model/Macro.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/contour/Edge.h"

/*
Convert from TopContour to LeftContour:
    xStart -> yStart
    xEnd -> yEnd
    yStart -> xEnd
    yEnd -> xStart
*/

LeftContour::LeftContour() {

}

LeftContour::~LeftContour() {

}

void LeftContour::initializeHeadAndTail(int originX, int originY) {
    head = Edge::createLeftEdge(-1e8, originY, originX);
    tail = Edge::createLeftEdge(originY, 1e8, originX);
}

int LeftContour::getOriginX() {
    return originY;
}

int LeftContour::getOriginY() {
    return originX;
}

void LeftContour::setMacroXStart(Macro *macro, int xStart) {
    macro->setYStart(xStart);
}

void LeftContour::setMacroXEnd(Macro *macro, int xEnd) {
    macro->setYEnd(xEnd);
}

void LeftContour::setMacroYStart(Macro *macro, int yStart) {
    macro->setXEnd(yStart);
}

void LeftContour::setMacroYEnd(Macro *macro, int yEnd) {
    macro->setXStart(yEnd);
}

int LeftContour::getMacroXStart(Macro *macro) {
    return macro->getYStart();
}

int LeftContour::getMacroXEnd(Macro *macro) {
    return macro->getYEnd();
}

int LeftContour::getMacroYStart(Macro *macro) {
    return macro->getXEnd();
}

int LeftContour::getMacroYEnd(Macro *macro) {
    return macro->getXStart();
}

int LeftContour::getMacroWidth(Macro *macro) {
    return macro->getHeight();
}

int LeftContour::getMacroHeight(Macro *macro) {
    return macro->getWidth();
}

Edge *LeftContour::createTopEdge(int xStart, int xEnd, int y) {
    return Edge::createLeftEdge(xStart, xEnd, y);
}

Edge *LeftContour::createMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->createLeftEdge();
}

Edge *LeftContour::getMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->getLeftEdge();
}

Edge *LeftContour::getMacroNodeBottomEdge(MacroNode *macroNode) {
    return macroNode->getRightEdge();
}

void LeftContour::setEdgeXStart(Edge *edge, int xStart) {
    edge->setYStart(xStart);
}

void LeftContour::setEdgeXEnd(Edge *edge, int xEnd) {
    edge->setYEnd(xEnd);
}

void LeftContour::setEdgeYStart(Edge *edge, int yStart) {
    edge->setXEnd(yStart);
}

void LeftContour::setEdgeYEnd(Edge *edge, int yEnd) {
    edge->setXStart(yEnd);
}

int LeftContour::getEdgeXStart(Edge *edge) {
    return edge->getYStart();
}

int LeftContour::getEdgeXEnd(Edge *edge) {
    return edge->getYEnd();
}

int LeftContour::getEdgeYStart(Edge *edge) {
    return edge->getXEnd();
}

int LeftContour::getEdgeYEnd(Edge *edge) {
    return edge->getXStart();
}

void LeftContour::initializeLocalMaxY() {
    localMaxY = 1e8;
}

void LeftContour::addToLocalMaxY(int value) {
    localMaxY -= value;
}

void LeftContour::initializeMaxMinXY() {
    maxX = -1e8;
    minX = 1e8;
    maxY = 1e8;
    minY = -1e8;
}

void LeftContour::initializeMaxY() {
    maxY = 1e8;
}

bool LeftContour::isX1Larger(int x1, int x2) {
    return x1 > x2;
}

bool LeftContour::isX1NotSmaller(int x1, int x2) {
    return x1 >= x2;
}

bool LeftContour::isX1Smaller(int x1, int x2) {
    return x1 < x2;
}

bool LeftContour::isX1NotLarger(int x1, int x2) {
    return x1 <= x2;
}

bool LeftContour::isY1Larger(int y1, int y2) {
    return y1 < y2;
}

bool LeftContour::isY1NotSmaller(int y1, int y2) {
    return y1 <= y2;
}

bool LeftContour::isY1Smaller(int y1, int y2) {
    return y1 > y2;
}

bool LeftContour::isY1NotLarger(int y1, int y2) {
    return y1 >= y2;
}

int LeftContour::getYDifference(int y1, int y2) {
    return y2 - y1;
}

int LeftContour::addToX(int x, int value) {
    return x + value;
}

int LeftContour::addToY(int y, int value) {
    return y - value;
}