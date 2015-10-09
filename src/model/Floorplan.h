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
    Calculate the range of immovables.
    It is called by createFromAuxFiles().
    */
    void calculateMinMaxImmovablesXY();
    /*
    Use the expanded range of immovables in
    calling createBins(double, double, double, double, double, double).
    */
    void createBins(double binWidth, double binHeight);
    /*
    Create Bins with the four inputs are the range of Bins.
    The Bins are still empty. Call addxxxMacrosToBins() to add Macros.
    CALL IT OR FloorplanWindow cannot display.
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
    /*
    Set the desired region, where Macros are prefered to be placed.
    Since the region will be converted to Bins,
    MAKE SURE that the region is inside the Bins and
    the region boundary is at leat one Bin from the Bins boundary.
    Call it after calling createBins().
    */
    void setDesiredRegion(double xStart, double yStart, double xEnd, double yEnd);
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
    Calculate the total area of both preplaced and movable Macros.
    */
    int calculateMacrosArea();
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
    /*
    More movable Macros outside the desired region and farther the Macros from the region,
    higher the count. It is a weighted count.
    The desired region is set by setDesiredRegion().
    */
    double countMovableMacrosOutsideDesiredRegion();
    int getMinX();
    int getMinY();
    int getMaxX();
    int getMaxY();
    double getMinImmovablesX();
    double getMinImmovablesY();
    double getMaxImmovablesX();
    double getMaxImmovablesY();
    int getDesiredRegionBinIStart();
    int getDesiredRegionBinIEnd();
    int getDesiredRegionBinJStart();
    int getDesiredRegionBinJEnd();

    /*
    Output the preplaced, movable Macros, Terminals and Cells to a .nodes file
    such that NTUplace3 can use it for prototyping.
    */
    void outputNodesForPrototyping(const char *nodesFilename);
    /*
    Output the preplaced, movable Macros, Terminals and Cells to a .pl file
    such that NTUplace3 can use it for prototyping.
    */
    void outputPlForPrototyping(const char *plFilename);

    /*
    Create a Floorplan from a .aux file and other related files.
    The files follows 2015 ICCAD Contest format.
    If read unsuccessful, return 0.
    It calls calculateMinMaxImmovablesXY().
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

    /*
    Desired region. xxxEnd means the range excludes the value.
    */
    int desiredRegionBinIStart;
    int desiredRegionBinIEnd;
    int desiredRegionBinJStart;
    int desiredRegionBinJEnd;
    std::vector<int> *iDistancesToDesiredRegion;
    std::vector<int> *jDistancesToDesiredRegion;
    int longestDistanceToDesiredRegion;

    double routabilityWeight;

    ICPTree *icpTree;
};

#endif