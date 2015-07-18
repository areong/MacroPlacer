#include "tree/icptree/contour/Edge.h"

Edge::Edge() {
    xStart = 0;
    xEnd = 0;
    yStart = 0;
    yEnd = 0;
    macroNode = 0;
    frontEdge = 0;
    backEdge = 0;
}

Edge::~Edge() {

}

void Edge::setXStart(int xStart) {
    this->xStart = xStart;
}

int Edge::getXStart() {
    return xStart;
}

void Edge::setXEnd(int xEnd) {
    this->xEnd = xEnd;
}

int Edge::getXEnd() {
    return xEnd;
}

void Edge::setYStart(int yStart) {
    this->yStart = yStart;
}

int Edge::getYStart() {
    return yStart;
}

void Edge::setYEnd(int yEnd) {
    this->yEnd = yEnd;
}

int Edge::getYEnd() {
    return yEnd;
}

void Edge::setMacroNode(MacroNode *macroNode) {
    this->macroNode = macroNode;
}

MacroNode *Edge::getMacroNode() {
    return macroNode;
}

void Edge::setFrontEdge(Edge *edge) {
    frontEdge = edge;
}

Edge *Edge::getFrontEdge() {
    return frontEdge;
}

void Edge::setBackEdge(Edge *edge) {
    backEdge = edge;
}

Edge *Edge::getBackEdge() {
    return backEdge;
}

Edge *Edge::createTopEdge(int xStart, int xEnd, int y) {
    Edge *edge = new Edge();
    edge->setXStart(xStart);
    edge->setXEnd(xEnd);
    edge->setYEnd(y);
    return edge;
}

Edge *Edge::createRightEdge(int yEnd, int yStart, int x) {
    Edge *edge = new Edge();
    edge->setYEnd(yEnd);
    edge->setYStart(yStart);
    edge->setXEnd(x);
    return edge;
}

Edge *Edge::createBottomEdge(int xEnd, int xStart, int y) {
    Edge *edge = new Edge();
    edge->setXEnd(xEnd);
    edge->setXStart(xStart);
    edge->setYStart(y);
    return edge;
}

Edge *Edge::createLeftEdge(int yStart, int yEnd, int x) {
    Edge *edge = new Edge();
    edge->setYStart(yStart);
    edge->setYEnd(yEnd);
    edge->setXStart(x);
    return edge;
}
