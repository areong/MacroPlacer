#include "model/Floorplan.h"
#include <set>
#include <stdexcept>
#include "model/Bin.h"
#include "model/Cell.h"
#include "model/Macro.h"
#include "model/Net.h"
#include "model/Terminal.h"
#include "tree/icptree/ICPTree.h"

Floorplan::Floorplan(std::vector<Macro *> *movableMacros, ICPTree *icpTree) {
    preplacedMacros = new std::vector<Macro *>();
    this->movableMacros = new std::vector<Macro *>(); // Don't forget "this"!
    cells = new std::vector<Cell *>();
    terminals = new std::vector<Terminal *>();
    nets = new std::vector<Net *>();
    binsRows = new std::vector<std::vector<Bin *> *>();

    macrosByName = new std::map<std::string, Macro *>();
    cellsByName = new std::map<std::string, Cell *>();
    terminalsByName = new std::map<std::string, Terminal *>();
    netsByName = new std::map<std::string, Net *>();

    minImmovablesX = 0;
    minImmovablesY = 0;
    maxImmovablesX = 1;
    maxImmovablesY = 1;

    minBinsX = 0;
    minBinsY = 0;
    maxBinsX = 1;
    maxBinsY = 1;
    binWidth = 1;
    binHeight = 1;
    numBinsRows = 0;
    numBinsCols = 0;

    routabilityWeight = 1;

    if (movableMacros != 0) {
        for (int i = 0; i < movableMacros->size(); ++i) {
            addMovableMacro(movableMacros->at(i));
        }
    }

    this->icpTree = icpTree;
}

Floorplan::~Floorplan() {
    for (int i = 0; i < preplacedMacros->size(); ++i) {
        delete preplacedMacros->at(i);
    }
    delete preplacedMacros;
    for (int i = 0; i < movableMacros->size(); ++i) {
        delete movableMacros->at(i);
    }
    delete movableMacros;
    for (int i = 0; i < cells->size(); ++i) {
        delete cells->at(i);
    }
    delete cells;
    for (int i = 0; i < terminals->size(); ++i) {
        delete terminals->at(i);
    }
    delete terminals;
    for (int i = 0; i < nets->size(); ++i) {
        delete nets->at(i);
    }
    delete nets;
    for (int i = 0; i < binsRows->size(); ++i) {
        for (int j = 0; j < binsRows->at(i)->size(); ++j) {
            delete binsRows->at(i)->at(j);
        }
        delete binsRows->at(i);
    }
    delete binsRows;

    delete macrosByName;
    delete cellsByName;
    delete terminalsByName;
    delete netsByName;

    delete icpTree;
}

void Floorplan::setICPTree(ICPTree *icpTree) {
    this->icpTree = icpTree;
}

ICPTree *Floorplan::getICPTree() {
    return icpTree;
}

void Floorplan::addPreplacedMacro(Macro *macro) {
    preplacedMacros->push_back(macro);
    (*macrosByName)[macro->getName()] = macro;
}

void Floorplan::addMovableMacro(Macro *macro) {
    movableMacros->push_back(macro);
    (*macrosByName)[macro->getName()] = macro;
}

void Floorplan::addCell(Cell *cell) {
    cells->push_back(cell);
    (*cellsByName)[cell->getName()] = cell;
}

void Floorplan::addTerminal(Terminal *terminal) {
    terminals->push_back(terminal);
    (*terminalsByName)[terminal->getName()] = terminal;
}

void Floorplan::addNet(Net *net) {
    nets->push_back(net);
    (*netsByName)[net->getName()] = net;
}

Macro *Floorplan::getMacroByName(std::string name) {
    try {
        return macrosByName->at(name);
    } catch (const std::out_of_range& oor) {
        return 0;
    }
}

Cell *Floorplan::getCellByName(std::string name) {
    try {
        return cellsByName->at(name);
    } catch (const std::out_of_range& oor) {
        return 0;
    }
}

Terminal *Floorplan::getTerminalByName(std::string name) {
    try {
        return terminalsByName->at(name);
    } catch (const std::out_of_range& oor) {
        return 0;
    }
}

Net *Floorplan::getNetByName(std::string name) {
    try {
        return netsByName->at(name);
    } catch (const std::out_of_range& oor) {
        return 0;
    }
}

void Floorplan::createBins(double binWidth, double binHeight) {
    minImmovablesX = 1e8;
    minImmovablesY = 1e8;
    maxImmovablesX = -1e8;
    maxImmovablesY = -1e8;
    // Calculate the range of Terminals.
    for (int i = 0; i < terminals->size(); ++i) {
        double x = terminals->at(i)->getX();
        double y = terminals->at(i)->getY();
        if (x < minImmovablesX) {
            minImmovablesX = x;
        }
        if (y < minImmovablesY) {
            minImmovablesY = y;
        }
        if (x > maxImmovablesX) {
            maxImmovablesX = x;
        }
        if (y > maxImmovablesY) {
            maxImmovablesY = y;
        }
    }
    // Calculate the range of preplacedMacros.
    for (int i = 0; i < preplacedMacros->size(); ++i) {
        Macro *macro = preplacedMacros->at(i);
        if (macro->getXStart() < minImmovablesX) {
            minImmovablesX = macro->getXStart();
        }
        if (macro->getYStart() < minImmovablesY) {
            minImmovablesY = macro->getYStart();
        }
        if (macro->getXEnd() > maxImmovablesX) {
            maxImmovablesX = macro->getXEnd();
        }
        if (macro->getYEnd() > maxImmovablesY) {
            maxImmovablesY = macro->getYEnd();
        }
    }
    double immovablesRegionWidth = maxImmovablesX - minImmovablesX;
    double immovablesRegionHeight = maxImmovablesY - minImmovablesY;
    double expandRatio = 2;
    createBins(minImmovablesX - expandRatio * immovablesRegionWidth,
        minImmovablesY - expandRatio * immovablesRegionHeight,
        maxImmovablesX + expandRatio * immovablesRegionWidth,
        maxImmovablesY + expandRatio * immovablesRegionHeight,
        binWidth, binHeight);
}

void Floorplan::createBins(double xStart, double yStart, double xEnd, double yEnd, double binWidth, double binHeight) {
    // Clear.
    for (int i = 0; i < binsRows->size(); ++i) {
        std::vector<Bin *> *binsRow = binsRows->at(i);
        for (int j = 0; j < binsRow->size(); ++j) {
            delete binsRow->at(j);
        }
        delete binsRow;
    }
    binsRows->clear();
    // Determine Bins range.
    this->binWidth = binWidth;
    this->binHeight = binHeight;
    minBinsX = xStart;
    minBinsY = yStart;
    double binsRegionWidth = xEnd - xStart;
    double binsRegionHeight = yEnd - yStart;
    numBinsCols = (int) (binsRegionWidth / binWidth);
    if (numBinsCols * binWidth < binsRegionWidth) {
        numBinsCols += 1;
    }
    numBinsRows = (int) (binsRegionHeight / binHeight);
    if (numBinsRows * binHeight < binsRegionHeight) {
        numBinsRows += 1;
    }
    maxBinsX = minBinsX + numBinsCols * binWidth;
    maxBinsY = minBinsY + numBinsRows * binHeight;
    // Create Bins.
    double currentXStart;
    double currentYStart = minBinsY;
    double currentXEnd;
    double currentYEnd = currentYStart + binHeight;
    for (int i = 0; i < numBinsRows; ++i) {
        currentXStart = minBinsX;
        currentXEnd = minBinsX + binWidth;
        std::vector<Bin *> *binsRow = new std::vector<Bin *>();
        for (int j = 0; j < numBinsCols; ++j) {
            Bin *bin = new Bin(currentXStart, currentYStart, currentXEnd, currentYEnd);
            binsRow->push_back(bin);
            currentXStart = currentXEnd;
            currentXEnd += binWidth;
        }
        binsRows->push_back(binsRow);
        currentYStart = currentYEnd;
        currentYEnd += binHeight;
    }
}

std::vector<std::vector<Bin *> *> *Floorplan::getBinsRows() {
    return binsRows;
}

double Floorplan::getMinBinsX() {
    return minBinsX;
}

double Floorplan::getMinBinsY() {
    return minBinsY;
}

double Floorplan::getMaxBinsX() {
    return maxBinsX;
}

double Floorplan::getMaxBinsY() {
    return maxBinsY;
}

std::vector<Bin *> *Floorplan::getBinsUnderRectangle(double xStart, double yStart, double xEnd, double yEnd) {
    int iStart = (int) ((yStart - minBinsY) / binHeight);
    int jStart = (int) ((xStart - minBinsX) / binWidth);
    int iEnd = (int) ((yEnd - minBinsY) / binHeight) + 1;
    int jEnd = (int) ((xEnd - minBinsX) / binWidth) + 1;
    if (iStart < 0) {
        iStart = 0;
    }
    if (jStart < 0) {
        jStart = 0;
    }
    if (iEnd > numBinsRows) {
        iEnd = numBinsRows;
    }
    if (jEnd > numBinsCols) {
        jEnd = numBinsCols;
    }
    std::vector<Bin *> *returnedBins = new std::vector<Bin *>();
    for (int i = iStart; i < iEnd; ++i) {
        for (int j = jStart; j < jEnd; ++j) {
            returnedBins->push_back(binsRows->at(i)->at(j));
        }
    }
    return returnedBins;
}

void Floorplan::addPreplacedMacrosToBins() {
    for (int i = 0; i < preplacedMacros->size(); ++i) {
        Macro *macro = preplacedMacros->at(i);
        std::vector<Bin *> *bins = getBinsUnderRectangle(macro->getXStart(),
            macro->getYStart(), macro->getXEnd(), macro->getYEnd());
        for (int j = 0; j < bins->size(); ++j) {
            bins->at(j)->addPreplacedMacro(macro);
        }
        delete bins;
    }
}

void Floorplan::clearBinsMovableMacros() {
    for (int i = 0; i < numBinsRows; ++i) {
        for (int j = 0; j < numBinsCols; ++j) {
            binsRows->at(i)->at(j)->clearMovableMacros();
        }
    }
}

void Floorplan::addMovableMacrosToBins() {
    for (int i = 0; i < movableMacros->size(); ++i) {
        Macro *macro = movableMacros->at(i);
        std::vector<Bin *> *bins = getBinsUnderRectangle(macro->getXStart(),
            macro->getYStart(), macro->getXEnd(), macro->getYEnd());
        for (int j = 0; j < bins->size(); ++j) {
            bins->at(j)->addMovableMacro(macro);
        }
        delete bins;
    }
}

void Floorplan::updatePinsPosition() {
    for (int i = 0; i < movableMacros->size(); ++i) {
        movableMacros->at(i)->updatePinsPosition();
    }
}

void Floorplan::setRoutabilityWeightForHPWL(double weight) {
    routabilityWeight = weight;
}

double Floorplan::getRoutabilityWeight() {
    return routabilityWeight;
}

int Floorplan::calculateMacrosAreaUnderRectangle(double xStart, double yStart, double xEnd, double yEnd) {
    // Collect all covered movable and preplaced Macros.
    std::vector<Bin *> *coveredBins = getBinsUnderRectangle(xStart, yStart, xEnd, yEnd);
    if (coveredBins->empty()) {
        delete coveredBins;
        return 0;
    }
    std::set<Macro *> *coveredMacros = new std::set<Macro *>();
    for (int i = 0; i < coveredBins->size(); ++i) {
        Bin *bin = coveredBins->at(i);
        std::vector<Macro *> *binPreplacedMacros = bin->getPreplacedMacros();
        std::vector<Macro *> *binMovableMacros = bin->getMovableMacros();
        for (int j = 0; j < binPreplacedMacros->size(); ++j) {
            coveredMacros->insert(binPreplacedMacros->at(j));
        }
        for (int j = 0; j < binMovableMacros->size(); ++j) {
            coveredMacros->insert(binMovableMacros->at(j));
        }
    }
    delete coveredBins;
    // Sum up the under-the-rectangle area of each Macro.
    // Assume all Macros do not overlap with each other.
    if (coveredMacros->empty()) {
        delete coveredMacros;
        return 0;
    }
    double area = 0;
    for (std::set<Macro *>::iterator it = coveredMacros->begin(); it != coveredMacros->end(); ++it) {
        area += (*it)->calculateAreaUnderRectangle(xStart, yStart, xEnd, yEnd);
    }
    delete coveredMacros;
    return area;
}

int Floorplan::calculateAreaOutOfBinsUnderRectangle(double xStart, double yStart, double xEnd, double yEnd) {
    // The area equals the area of the rectangle subtracted by
    // the overlapping area between the rectangle and the bins.
    double overlappingArea = 0;
    double minX = (minBinsX > xStart) ? minBinsX : xStart;
    double minY = (minBinsY > yStart) ? minBinsY : yStart;
    double maxX = (maxBinsX < xEnd) ? maxBinsX : xEnd;
    double maxY = (maxBinsY < yEnd) ? maxBinsY : yEnd;
    if (maxX > minX && maxY > minY) {
        overlappingArea = (maxX - minX) * (maxY - minY);
    }
    return (xEnd - xStart) * (yEnd - yStart) - overlappingArea;
}

int Floorplan::getMaxX() {
    return icpTree->getMaxX();
    //return maxBinsX;
}

int Floorplan::getMinX() {
    return icpTree->getMinX();
    //return minBinsX;
}

int Floorplan::getMaxY() {
    return icpTree->getMaxY();
    //return maxBinsY;
}

int Floorplan::getMinY() {
    return icpTree->getMinY();
    //return minBinsY;
}