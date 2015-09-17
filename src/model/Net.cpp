#include "model/Net.h"
#include "model/Floorplan.h"
#include "model/Pin.h"

Net::Net(Floorplan *floorplan, std::string name) {
    this->floorplan = floorplan;
    this->name = name;
    macroPins = new std::vector<Pin *>();
    cellPins = new std::vector<Pin *>();
    terminalPins = new std::vector<Pin *>();
    minPinsX = 0;
    minPinsY = 0;
    maxPinsX = 0;
    maxPinsY = 0;
}

Net::~Net() {
    delete macroPins;
    delete cellPins;
    delete terminalPins;
}

std::string Net::getName() {
    return name;
}

void Net::addMacroPin(Pin *pin) {
    macroPins->push_back(pin);
}

void Net::addCellPin(Pin *pin) {
    cellPins->push_back(pin);
}

void Net::addTerminalPin(Pin *pin) {
    terminalPins->push_back(pin);
}

std::vector<Pin *> *Net::getMacroPins() {
    return macroPins;
}

std::vector<Pin *> *Net::getCellPins() {
    return cellPins;
}

std::vector<Pin *> *Net::getTerminalPins() {
    return terminalPins;
}

double Net::calculateHpwl() {
    minPinsX = 1e8;
    minPinsY = 1e8;
    maxPinsX = -1e8;
    maxPinsY = -1e8;
    for (int i = 0; i < macroPins->size(); i++) {
        double pinX = macroPins->at(i)->getX();
        double pinY = macroPins->at(i)->getY();
        if (pinX < minPinsX) minPinsX = pinX;
        if (pinX > maxPinsX) maxPinsX = pinX;
        if (pinY < minPinsY) minPinsY = pinY;
        if (pinY > maxPinsY) maxPinsY = pinY;
    }
    for (int i = 0; i < terminalPins->size(); i++) {
        double pinX = terminalPins->at(i)->getX();
        double pinY = terminalPins->at(i)->getY();
        if (pinX < minPinsX) minPinsX = pinX;
        if (pinX > maxPinsX) maxPinsX = pinX;
        if (pinY < minPinsY) minPinsY = pinY;
        if (pinY > maxPinsY) maxPinsY = pinY;
    }
    if (maxPinsX < minPinsX || maxPinsY - minPinsY) {
        return 0;
    } else {
        return maxPinsX - minPinsX + maxPinsY - minPinsY;
    }
}

double Net::calculateRoutabilityHpwl() {
    double hpwl = calculateHpwl();
    if (hpwl == 0) {
        return 0;
    }
    double totalArea = (maxPinsX - minPinsX) * (maxPinsY - minPinsY);
    double macrosArea = floorplan->calculateMacrosAreaUnderRectangle(minPinsX,
        minPinsY, maxPinsX, maxPinsY);
    double outOfBinsArea = floorplan->calculateAreaOutOfBinsUnderRectangle(
        minPinsX, minPinsY, maxPinsX, maxPinsY);
    double unroutableRatio = 0;
    if (totalArea > 0) {
        unroutableRatio = (macrosArea + outOfBinsArea) / totalArea;
    }
    return (1 + floorplan->getRoutabilityWeight() * unroutableRatio) * hpwl;
}
