#include "model/Macro.h"

Macro::Macro() {
    width = 1;
    height = 1;
    xStart = 0;
    xEnd = 1;
    yStart = 0;
    yEnd = 1;
}

Macro::Macro(int width, int height) {
    this->width = width;
    this->height = height;
    xStart = 0;
    xEnd = 1;
    yStart = 0;
    yEnd = 1;
}

Macro::~Macro() {

}

void Macro::setWidth(int width) {
    this->width = width;
}

int Macro::getWidth() {
    return width;
}

void Macro::setHeight(int height) {
    this->height = height;
}

int Macro::getHeight() {
    return height;
}

void Macro::setXStart(int xStart) {
    this->xStart = xStart;
    xEnd = xStart + width;
}

int Macro::getXStart() {
    return xStart;
}

void Macro::setXEnd(int xEnd) {
    this->xEnd = xEnd;
    xStart = xEnd - width;
}

int Macro::getXEnd() {
    return xEnd;
}

void Macro::setYStart(int yStart) {
    this->yStart = yStart;
    yEnd = yStart + height;
}

int Macro::getYStart() {
    return yStart;
}

void Macro::setYEnd(int yEnd) {
    this->yEnd = yEnd;
    yStart = yEnd - height;
}

int Macro::getYEnd() {
    return yEnd;
}

Macro *Macro::copy() {
    Macro *macro = new Macro(width, height);
    macro->setXStart(xStart);
    macro->setYStart(yStart);
    return macro;
}