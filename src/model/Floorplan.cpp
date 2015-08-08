#include "model/Floorplan.h"
#include "model/Macro.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/MacroNode.h"

Floorplan::Floorplan(std::vector<Macro *> *macros, std::vector<MacroNode *> *macroNodes,
    ICPTree *icpTree) {
    this->macros = macros;
    this->macroNodes = macroNodes;
    this->icpTree = icpTree;
}

Floorplan::~Floorplan() {
    delete icpTree; // Also delete all MacroNodes in macroNodes.
    delete macroNodes;
    for (int i = 0; i < macros->size(); i++) {
        delete macros->at(i);
    }
    delete macros;
}

std::vector<Macro *> *Floorplan::getMacros() {
    return macros;
}

std::vector<MacroNode *> *Floorplan::getMacroNodes() {
    return macroNodes;
}

ICPTree *Floorplan::getICPTree() {
    return icpTree;
}

int Floorplan::getMaxX() {
    return icpTree->getMaxX();
}

int Floorplan::getMinX() {
    return icpTree->getMinX();
}

int Floorplan::getMaxY() {
    return icpTree->getMaxY();
}

int Floorplan::getMinY() {
    return icpTree->getMinY();
}
