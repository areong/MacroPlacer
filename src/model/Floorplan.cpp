#include "model/Floorplan.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include "model/Bin.h"
#include "model/Cell.h"
#include "model/Macro.h"
#include "model/Module.h"
#include "model/Net.h"
#include "model/Pin.h"
#include "model/Terminal.h"
#include "tree/icptree/ICPTree.h"
#include "utils/Utils.h"

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

std::vector<Macro *> *Floorplan::getPreplacedMacros() {
    return preplacedMacros;
}

std::vector<Macro *> *Floorplan::getMovableMacros() {
    return movableMacros;
}

std::vector<Cell *> *Floorplan::getCells() {
    return cells;
}

std::vector<Terminal *> *Floorplan::getTerminals() {
    return terminals;
}

std::vector<Net *> *Floorplan::getNets() {
    return nets;
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

void Floorplan::setRoutabilityWeightOfHpwl(double weight) {
    routabilityWeight = weight;
}

double Floorplan::getRoutabilityWeight() {
    return routabilityWeight;
}

int Floorplan::calculateCellsArea() {
    int area = 0;
    for (int i = 0; i < cells->size(); ++i) {
        area += cells->at(i)->getWidth() * cells->at(i)->getHeight();
    }
    return area;
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

double Floorplan::calculateNetsHpwl() {
    double sumHpwl = 0;
    for (int i = 0; i < nets->size(); ++i) {
        Net *net = nets->at(i);
        if (net->getMacroPins()->size() == 0 && net->getTerminalPins()->size() == 0) {
            continue;
        }
        sumHpwl += net->calculateHpwl();
    }
    return sumHpwl;
}

double Floorplan::calculateNetsRoutabilityHpwl() {
    double sumHpwl = 0;
    for (int i = 0; i < nets->size(); ++i) {
        Net *net = nets->at(i);
        if (net->getMacroPins()->size() == 0 && net->getTerminalPins()->size() == 0) {
            continue;
        }
        sumHpwl += net->calculateRoutabilityHpwl();
    }
    return sumHpwl;
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

Floorplan *Floorplan::createFromAuxFiles(const char *auxFilename) {
    Floorplan *floorplan = 0;

    // Save filenames to a map.
    std::map<std::string, std::string> filenamesByType;

    // Aux file, one line:
    //   RowBasedPlacement :  adaptec1.nodes  adaptec1.nets  adaptec1.wts
    //   adaptec1.pl  adaptec1.scl adaptec1.shapes adaptec1.route
    std::ifstream auxFile(auxFilename);
    if (auxFile.is_open()) {
        std::string line;
        std::getline(auxFile, line);
        std::vector<std::string> *tokens = Utils::splitString(line, " :\n\r\t");
        for (int i = 1; i < tokens->size(); ++i) {
            int iDot = tokens->at(i).find('.');
            std::string type = tokens->at(i).substr(iDot + 1, tokens->at(i).length() - iDot - 1);
            filenamesByType[type] = tokens->at(i);
        }
        delete tokens;
        auxFile.close();
    } else {
        return 0;
    }

    // Check and get filenames.
    std::string nodesFilename;
    std::string plFilename;
    std::string netsFilename;
    try {
        nodesFilename = filenamesByType.at("nodes");
        plFilename = filenamesByType.at("pl");
        netsFilename = filenamesByType.at("nets");
    } catch (const std::out_of_range& oor) {
        return 0;
    }
    floorplan = new Floorplan();

    // Read nodes.
    std::ifstream nodesFile(nodesFilename.c_str());
    if (nodesFile.is_open()) {
        std::string line;
        // Ignore lines until the line starts with "NumT".
        while (true) {
            std::getline(nodesFile, line);
            if (line.length() >= 4 && line.compare(0, 4, "NumT") == 0) {
                break;
            }    
        }
        
        while (std::getline(nodesFile, line)) {
            std::vector<std::string> *tokens = Utils::splitString(line, "\t :\n\r");
            if (tokens->size() < 3) {
                continue;   // An empty line
            }
            std::string name = tokens->at(0);
            int width = atoi(tokens->at(1).c_str());
            int height = atoi(tokens->at(2).c_str());
            if (tokens->size() == 3) {
                if (width == 0 && height == 0) {
                    // A Terminal
                    Terminal *terminal = new Terminal(name);
                    floorplan->addTerminal(terminal);
                } else {
                    // A Cell
                    Cell *cell = new Cell(width, height, name);
                    floorplan->addCell(cell);
                }
            } else if (tokens->size() == 4 && tokens->at(3) == "terminal") {
                // A Macro
                Macro *macro = new Macro(width, height, name);
                floorplan->addMovableMacro(macro);
            }
            delete tokens;
        }
        nodesFile.close();
    } else {
        return 0;
    }

    // Read pl.
    std::ifstream plFile(plFilename.c_str());
    if (plFile.is_open()) {
        std::string line;
        // Ignore the first line.
        std::getline(plFile, line);

        while (std::getline(plFile, line)) {
            std::vector<std::string> *tokens = Utils::splitString(line, "\t :\n\r");
            if (tokens->size() < 3) {
                continue;   // An empty line
            }
            if (tokens->at(0)[0] == '#') {
                continue;   // Ignore comment.
            }
            std::string name = tokens->at(0);
            int x = atoi(tokens->at(1).c_str());
            int y = atoi(tokens->at(2).c_str());
            // Ignore Cells.
            Terminal *terminal = floorplan->getTerminalByName(name);
            if (terminal != 0) {
                // A Terminal.
                terminal->setPosition(x, y);
            }
            delete tokens;
        }
        plFile.close();
    } else {
        return 0;
    }

    // Read nets.
    std::ifstream netsFile(netsFilename.c_str());
    if (netsFile.is_open()) {
        std::string line;
        // Ignore lines until the line starts with "NumP".
        while (true) {
            std::getline(netsFile, line);
            if (line.length() >= 4 && line.compare(0, 4, "NumP") == 0) {
                break;
            } 
        }

        Net *net = 0;
        while (std::getline(netsFile, line)) {
            std::vector<std::string> *tokens = Utils::splitString(line, "\t :\n\r");
            if (tokens->size() < 3) {
                continue;   // An empty line
            } else if (tokens->size() == 3) {
                // A new Net
                std::string name = tokens->at(2);
                net = new Net(floorplan, name);
                floorplan->addNet(net);
            } else {
                // A Pin of the current Net.
                std::string name = tokens->at(0);
                double offsetX = atof(tokens->at(2).c_str());
                double offsetY = atof(tokens->at(3).c_str());
                // Find whether it belongs to a Cell, a Terminal or a Macro.
                Module *module = 0;
                Cell *cell = floorplan->getCellByName(name);
                int pinType = 0;
                if (cell != 0) {
                    offsetX += (double) cell->getWidth() / 2;
                    offsetY += (double) cell->getHeight() / 2;
                    module = cell;
                    pinType = 1;
                } else {
                    module = floorplan->getTerminalByName(name);
                    pinType = 2;
                    if (module == 0) {
                        Macro *macro = floorplan->getMacroByName(name);
                        if (macro != 0) {
                            offsetX += (double) macro->getWidth() / 2;
                            offsetY += (double) macro->getHeight() / 2;
                            module = macro;
                            pinType = 3;
                        } else {
                            continue;
                        }
                    }
                }
                // Check the Pin exists or not.
                Pin *pin = module->getPinByOffset(offsetX, offsetY);
                if (pin == 0) {
                    // It is a new Pin, create and add it.
                    pin = new Pin(offsetX, offsetY);
                    module->addPin(pin);
                }
                // Add the Pin to the Net.
                switch (pinType) {
                case 1:
                    net->addCellPin(pin);
                    break;
                case 2:
                    net->addTerminalPin(pin);
                    break;
                case 3:
                    net->addMacroPin(pin);
                    break;
                default:
                    break;
                }
            }
            delete tokens;
        }
        netsFile.close();
    } else {
        return 0;
    }

    return floorplan;
}