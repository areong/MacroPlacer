#include "model/Bin.h"

Bin::Bin(double xStart, double yStart, double xEnd, double yEnd) {
    this->xStart = xStart;
    this->yStart = yStart;
    this->xEnd = xEnd;
    this->yEnd = yEnd;
    preplacedMacros = new std::vector<Macro *>();
    movableMacros = new std::vector<Macro *>();
}

Bin::~Bin() {
    delete preplacedMacros;
    delete movableMacros;
}

void Bin::addPreplacedMacro(Macro *macro) {
    preplacedMacros->push_back(macro);
}

std::vector<Macro *> *Bin::getPreplacedMacros() {
    return preplacedMacros;
}

void Bin::addMovableMacro(Macro *macro) {
    movableMacros->push_back(macro);
}

std::vector<Macro *> *Bin::getMovableMacros() {
    return movableMacros;
}

void Bin::clearMovableMacros() {
    movableMacros->clear();
}

double Bin::getXStart() {
    return xStart;
}

double Bin::getYStart() {
    return yStart;
}

double Bin::getXEnd() {
    return xEnd;
}

double Bin::getYEnd() {
    return yEnd;
}
