#ifndef MODEL_FLOORPLAN_H_
#define MODEL_FLOORPLAN_H_

#include <map>
#include <string>
#include <vector>

class Bin;
class Cell;
class ICPTree;
class Macro;
class Net;
class Terminal;

class Floorplan {
public:
    //Floorplan();
    /*
    Add Macros by addMovableMacro().
    */
    Floorplan(std::vector<Macro *> *movableMacros=0, ICPTree *icpTree=0);
    /*
    Delete all Bins, Macros, Cells, Terminals and Nets.
    Pins are deleted when Modules are deleted.
    */
    ~Floorplan();
    void setICPTree(ICPTree *icpTree);
    ICPTree *getICPTree();
    void addPreplacedMacro(Macro *macro);
    void addMovableMacro(Macro *macro);
    void addCell(Cell *cell);
    void addTerminal(Terminal *terminal);
    void addNet(Net *net);
    /*
    If the name does not match, returns 0.
    */
    Macro *getMacroByName(std::string name);
    /*
    If the name does not match, returns 0.
    */
    Cell *getCellByName(std::string name);
    /*
    If the name does not match, returns 0.
    */
    Terminal *getTerminalByName(std::string name);
    /*
    If the name does not match, returns 0.
    */
    Net *getNetByName(std::string name);
    std::vector<Macro *> *getPreplacedMacros();
    std::vector<Macro *> *getMovableMacros();
    std::vector<Cell *> *getCells();
    std::vector<Terminal *> *getTerminals();
    std::vector<Net *> *getNets();
    /*
    Calculate the position range of Terminals and preplacedMacros
    and then call createBins(double, double, double, double, double, double).
    */
    void createBins(double binWidth, double binHeight);
    /*
    Create Bins with the four inputs are the range of Bins.
    The Bins are still empty. Call addxxxMacrosToBins() to add Macros.
    */
    void createBins(double xStart, double yStart, double xEnd, double yEnd, double binWidth, double binHeight);
    std::vector<std::vector<Bin *> *> *getBinsRows();
    double getMinBinsX();
    double getMinBinsY();
    double getMaxBinsX();
    double getMaxBinsY();
    /*
    Return a vector containing the Bins overlapping with the input x y range.
    PLEASE DELETE the returned vector.
    */
    std::vector<Bin *> *getBinsUnderRectangle(double xStart, double yStart, double xEnd, double yEnd);
    void addPreplacedMacrosToBins();
    void clearBinsMovableMacros();
    void addMovableMacrosToBins();
    /*
    Update the position of Pins of movableMacros.
    */
    void updatePinsPosition();
    void setRoutabilityWeightOfHpwl(double weight);
    double getRoutabilityWeight();
    /*
    Calculate the total area of Cells.
    */
    int calculateCellsArea();
    int calculateMacrosAreaUnderRectangle(double xStart, double yStart, double xEnd, double yEnd);
    int calculateAreaOutOfBinsUnderRectangle(double xStart, double yStart, double xEnd, double yEnd);
    /*
    Calculate the sum of hpwl of all Nets except for those Nets that do not have
    macroPins nor terminalPins. I.e., Nets with cellPins only are ignored.
    */
    double calculateNetsHpwl();
    double calculateNetsRoutabilityHpwl();
    int getMaxX();
    int getMinX();
    int getMaxY();
    int getMinY();

    /*
    Create a Floorplan from a .aux file and other related files.
    The files follows 2015 ICCAD Contest format.
    If read unsuccessful, return 0.
    */
    static Floorplan *createFromAuxFiles(const char *auxFilename);
    
private:
    std::vector<Macro *> *preplacedMacros;
    std::vector<Macro *> *movableMacros;
    std::vector<Cell *> *cells;
    std::vector<Terminal *> *terminals;
    std::vector<Net *> *nets;
    std::vector<std::vector<Bin *> *> *binsRows;

    std::map<std::string, Macro *> *macrosByName;
    std::map<std::string, Cell *> *cellsByName;
    std::map<std::string, Terminal *> *terminalsByName;
    std::map<std::string, Net *> *netsByName;

    /*
    The x y range of Terminals and preplacedMacros.
    */
    double minImmovablesX;
    double minImmovablesY;
    double maxImmovablesX;
    double maxImmovablesY;

    /*
    The x y range of Bins.
    */
    double minBinsX;
    double minBinsY;
    double maxBinsX;
    double maxBinsY;
    double binWidth;
    double binHeight;
    int numBinsRows;
    int numBinsCols;

    double routabilityWeight;

    ICPTree *icpTree;
};

#endif