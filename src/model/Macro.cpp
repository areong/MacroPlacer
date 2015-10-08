#include "model/Macro.h"

Macro::Macro(int width, int height, std::string name) : Module(name) {
    this->width = width;
    this->height = height;
    calculateArea();
    calculateAspectRatio();
    xStart = 0;
    xEnd = 1;
    yStart = 0;
    yEnd = 1;
}

Macro::~Macro() {

}

void Macro::setWidth(int width) {
    this->width = width;
    calculateArea();
    calculateAspectRatio();
}

int Macro::getWidth() {
    return width;
}

void Macro::setHeight(int height) {
    this->height = height;
    calculateArea();
    calculateAspectRatio();
}

int Macro::getHeight() {
    return height;
}

void Macro::calculateArea() {
    area = width * height;
}

int Macro::getArea() {
    return area;
}

void Macro::calculateAspectRatio() {
    aspectRatio = (double) height / (double) width;
}

double Macro::getAspectRatio() {
    return aspectRatio;
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

double Macro::getPinsOriginX() {
    switch(rotation) {
    case 0:
        return xStart;
    case 1:
        return xEnd;
    case 2:
        return xEnd;
    case 3:
        return xStart;
    default:
        return xStart;
    }
}

double Macro::getPinsOriginY() {
    switch(rotation) {
    case 0:
        return yStart;
    case 1:
        return yStart;
    case 2:
        return yEnd;
    case 3:
        return yEnd;
    default:
        return yStart;
    }
}

void Macro::rotate(bool counterclockwise) {
    Module::rotate(counterclockwise);
    double temp = width;
    width = height;
    height = temp;
}

double Macro::calculateAreaUnderRectangle(double xStart, double yStart, double xEnd, double yEnd) {
    double minX = (this->xStart > xStart) ? this->xStart : xStart;
    double minY = (this->yStart > yStart) ? this->yStart : yStart;
    double maxX = (this->xEnd < xEnd) ? this->xEnd : xEnd;
    double maxY = (this->yEnd < yEnd) ? this->yEnd : yEnd;
    if (maxX > minX && maxY > minY) {
        return (maxX - minX) * (maxY - minY);
    } else {
        return 0;
    }
}

Macro *Macro::copy() {
    Macro *macro = new Macro(width, height, getName());
    macro->setXStart(xStart);
    macro->setYStart(yStart);
    return macro;
}