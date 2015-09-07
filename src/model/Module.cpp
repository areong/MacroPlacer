#include "model/Module.h"
#include "model/Pin.h"

Module::Module(std::string name) {
    this->name = name;
    pins = new std::vector<Pin *>();
    rotation = 0;
}

Module::~Module() {
    for (int i = 0; i < pins->size(); i++) {
        delete pins->at(i);
    }
    delete pins;
}

std::string Module::getName() {
    return name;
}

void Module::addPin(Pin *pin) {
    pins->push_back(pin);
    pin->setModule(this);
}

Pin *Module::getPinByOffset(double offsetX, double offsetY) {
    for (int i = 0; i < pins->size(); i++) {
        Pin *pin = pins->at(i);
        if (pin->getOffsetX() == offsetX && pin->getOffsetY() == offsetY) {
            return pin;
        }
    }
    return 0;
}

void Module::updatePinsPosition() {
    double pinsOriginX = getPinsOriginX();
    double pinsOriginY = getPinsOriginY();
    // switch() is called only once.
    // If delegate update to each Pin, switch() will be called
    // many times.
    switch(rotation) {
    case 0:
        for (int i = 0; i < pins->size(); i++) {
            Pin *pin = pins->at(i);
            pin->setX(pinsOriginX + pin->getOffsetX());
            pin->setY(pinsOriginY + pin->getOffsetY());
        }
        break;
    case 1:
        for (int i = 0; i < pins->size(); i++) {
            Pin *pin = pins->at(i);
            pin->setX(pinsOriginX - pin->getOffsetY());
            pin->setY(pinsOriginY + pin->getOffsetX());
        }
        break;
    case 2:
        for (int i = 0; i < pins->size(); i++) {
            Pin *pin = pins->at(i);
            pin->setX(pinsOriginX - pin->getOffsetX());
            pin->setY(pinsOriginY - pin->getOffsetY());
        }
        break;
    case 3:
        for (int i = 0; i < pins->size(); i++) {
            Pin *pin = pins->at(i);
            pin->setX(pinsOriginX + pin->getOffsetY());
            pin->setY(pinsOriginY - pin->getOffsetX());
        }
        break;
    default:
        for (int i = 0; i < pins->size(); i++) {
            Pin *pin = pins->at(i);
            pin->setX(pinsOriginX + pin->getOffsetX());
            pin->setY(pinsOriginY + pin->getOffsetY());
        }
        break;
    }
}

void Module::rotate(bool counterclockwise) {
    if (counterclockwise) {
        rotation = (rotation += 1) % 4;
    } else {
        rotation = (rotation -= 1) % 4;
    }
}

int Module::getRotation() {
    return rotation;
}
