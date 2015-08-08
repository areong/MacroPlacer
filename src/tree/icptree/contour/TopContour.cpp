#include "tree/icptree/contour/TopContour.h"
#include "model/Macro.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/contour/Edge.h"

TopContour::TopContour() {

}

TopContour::~TopContour() {

}

void TopContour::initializeHeadAndTail(int originX, int originY) {
    head = Edge::createTopEdge(-1e8, originX, originY);
    tail = Edge::createTopEdge(originX, 1e8, originY);
}

int TopContour::getOriginX() {
    return originX;
}

int TopContour::getOriginY() {
    return originY;
}

void TopContour::setMacroXStart(Macro *macro, int xStart) {
    macro->setXStart(xStart);
}

void TopContour::setMacroXEnd(Macro *macro, int xEnd) {
    macro->setXEnd(xEnd);
}

void TopContour::setMacroYStart(Macro *macro, int yStart) {
    macro->setYStart(yStart);
}

void TopContour::setMacroYEnd(Macro *macro, int yEnd) {
    macro->setYEnd(yEnd);
}

int TopContour::getMacroXStart(Macro *macro) {
    return macro->getXStart();
}

int TopContour::getMacroXEnd(Macro *macro) {
    return macro->getXEnd();
}

int TopContour::getMacroYStart(Macro *macro) {
    return macro->getYStart();
}

int TopContour::getMacroYEnd(Macro *macro) {
    return macro->getYEnd();
}

int TopContour::getMacroWidth(Macro *macro) {
    return macro->getWidth();
}

int TopContour::getMacroHeight(Macro *macro) {
    return macro->getHeight();
}

Edge *TopContour::createTopEdge(int xStart, int xEnd, int y) {
    return Edge::createTopEdge(xStart, xEnd, y);
}

Edge *TopContour::createMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->createTopEdge();
}

Edge *TopContour::getMacroNodeTopEdge(MacroNode *macroNode) {
    return macroNode->getTopEdge();
}

Edge *TopContour::getMacroNodeBottomEdge(MacroNode *macroNode) {
    return macroNode->getBottomEdge();
}

void TopContour::setEdgeXStart(Edge *edge, int xStart) {
    edge->setXStart(xStart);
}

void TopContour::setEdgeXEnd(Edge *edge, int xEnd) {
    edge->setXEnd(xEnd);
}

void TopContour::setEdgeYStart(Edge *edge, int yStart) {
    edge->setYStart(yStart);
}

void TopContour::setEdgeYEnd(Edge *edge, int yEnd) {
    edge->setYEnd(yEnd);
}

int TopContour::getEdgeXStart(Edge *edge) {
    return edge->getXStart();
}

int TopContour::getEdgeXEnd(Edge *edge) {
    return edge->getXEnd();
}

int TopContour::getEdgeYStart(Edge *edge) {
    return edge->getYStart();
}

int TopContour::getEdgeYEnd(Edge *edge) {
    return edge->getYEnd();
}

void TopContour::initializeLocalMaxY() {
    localMaxY = -1e8;
}

void TopContour::addToLocalMaxY(int value) {
    localMaxY += value;
}

void TopContour::initializeMaxMinXY() {
    maxX = -1e8;
    minX = 1e8;
    maxY = -1e8;
    minY = 1e8;
}

void TopContour::initializeMaxY() {
    maxY = -1e8;
}

bool TopContour::isX1Larger(int x1, int x2) {
    return x1 > x2;
}

bool TopContour::isX1NotSmaller(int x1, int x2) {
    return x1 >= x2;
}

bool TopContour::isX1Smaller(int x1, int x2) {
    return x1 < x2;
}

bool TopContour::isX1NotLarger(int x1, int x2) {
    return x1 <= x2;
}

bool TopContour::isY1Larger(int y1, int y2) {
    return y1 > y2;
}

bool TopContour::isY1NotSmaller(int y1, int y2) {
    return y1 >= y2;
}

bool TopContour::isY1Smaller(int y1, int y2) {
    return y1 < y2;
}

bool TopContour::isY1NotLarger(int y1, int y2) {
    return y1 <= y2;
}

int TopContour::getYDifference(int y1, int y2) {
    return y1 - y2;
}

int TopContour::addToX(int x, int value) {
    return x + value;
}

int TopContour::addToY(int y, int value) {
    return y + value;
}