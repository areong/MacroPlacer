#include "tree/icptree/contour/RightContour.h"
#include "model/Macro.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/contour/Edge.h"

/*
Convert from TopContour to RightContour:
    xStart -> yEnd
    xEnd -> yStart
    yStart -> xStart
    yEnd -> xEnd
*/

RightContour::RightContour() {

}

RightContour::~RightContour() {

}

void RightContour::initializeHeadAndTail(int originX, int originY) {
    head = Edge::createRightEdge(1e8, originY, originX);
    tail = Edge::createRightEdge(originY, -1e8, originX);
}

int RightContour::getOriginX() {
    return originY;
}

int RightContour::getOriginY() {
    return originX;
}

void RightContour::setMacroXStart(Macro *macro, int xStart) {
    macro->setYEnd(xStart);
}

void RightContour::setMacroXEnd(Macro *macro, int xEnd) {
    macro->setYStart(xEnd);
}

void RightContour::setMacroYStart(Macro *macro, int yStart) {
    macro->setXStart(yStart);
}

void RightContour::setMacroYEnd(Macro *macro, int yEnd) {
    macro->setXEnd(yEnd);
}

int RightContour::getMacroXStart(Macro *macro) {
    return macro->getYEnd();
}

int RightContour::getMacroXEnd(Macro *macro) {
    return macro->getYStart();
}

int RightContour::getMacroYStart(Macro *macro) {
    return macro->getXStart();
}

int RightContour::getMacroYEnd(Macro *macro) {
    return macro->getXEnd();
}

int RightContour::getMacroWidth(Macro *macro) {
    return macro->getHeight();
}

int RightContour::getMacroHeight(Macro *macro) {
    return macro->getWidth();
}

Edge *RightContour::createTopEdge(int xStart, int xEnd, int y) {
    return Edge::createRightEdge(xStart, xEnd, y);
}

Edge *RightContour::createMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->createRightEdge();
}

Edge *RightContour::getMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->getRightEdge();
}

Edge *RightContour::getMacroNodeBottomEdge(MacroNode *macroNode) {
    return macroNode->getLeftEdge();
}

void RightContour::setEdgeXStart(Edge *edge, int xStart) {
    edge->setYEnd(xStart);
}

void RightContour::setEdgeXEnd(Edge *edge, int xEnd) {
    edge->setYStart(xEnd);
}

void RightContour::setEdgeYStart(Edge *edge, int yStart) {
    edge->setXStart(yStart);
}

void RightContour::setEdgeYEnd(Edge *edge, int yEnd) {
    edge->setXEnd(yEnd);
}

int RightContour::getEdgeXStart(Edge *edge) {
    return edge->getYEnd();
}

int RightContour::getEdgeXEnd(Edge *edge) {
    return edge->getYStart();
}

int RightContour::getEdgeYStart(Edge *edge) {
    return edge->getXStart();
}

int RightContour::getEdgeYEnd(Edge *edge) {
    return edge->getXEnd();
}

void RightContour::initializeLocalMaxY() {
    localMaxY = -1e8;
}

void RightContour::addToLocalMaxY(int value) {
    localMaxY += value;
}

void RightContour::initializeMaxMinXY() {
    maxX = 1e8;
    minX = -1e8;
    maxY = -1e8;
    minY = 1e8;
}

void RightContour::initializeMaxY() {
    maxY = -1e8;
}

bool RightContour::isX1Larger(int x1, int x2) {
    return x1 < x2;
}

bool RightContour::isX1NotSmaller(int x1, int x2) {
    return x1 <= x2;
}

bool RightContour::isX1Smaller(int x1, int x2) {
    return x1 > x2;
}

bool RightContour::isX1NotLarger(int x1, int x2) {
    return x1 >= x2;
}

bool RightContour::isY1Larger(int y1, int y2) {
    return y1 > y2;
}

bool RightContour::isY1NotSmaller(int y1, int y2) {
    return y1 >= y2;
}

bool RightContour::isY1Smaller(int y1, int y2) {
    return y1 < y2;
}

bool RightContour::isY1NotLarger(int y1, int y2) {
    return y1 <= y2;
}

int RightContour::getYDifference(int y1, int y2) {
    return y1 - y2;
}

int RightContour::addToX(int x, int value) {
    return x - value;
}

int RightContour::addToY(int y, int value) {
    return y + value;
}