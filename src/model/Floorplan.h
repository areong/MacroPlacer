#ifndef MODEL_FLOORPLAN_H_
#define MODEL_FLOORPLAN_H_

#include <vector>

class Macro;
class MacroNode;
class ICPTree;

class Floorplan {
public:
    Floorplan(std::vector<Macro *> *macros, std::vector<MacroNode *> *macroNodes,
        ICPTree *icpTree);
    ~Floorplan();
    std::vector<Macro *> *getMacros();
    std::vector<MacroNode *> *getMacroNodes();
    void setICPTree(ICPTree *icpTree);
    ICPTree *getICPTree();
    int getMaxX();
    int getMinX();
    int getMaxY();
    int getMinY();
    
private:
    std::vector<Macro *> *macros;
    std::vector<MacroNode *> *macroNodes;
    ICPTree *icpTree;
};

#endif