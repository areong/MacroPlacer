#ifndef TREE_ICPTREE_SA_FLOORPLANSTATE_H_
#define TREE_ICPTREE_SA_FLOORPLANSTATE_H_

#include "sa/State.h"

class Floorplan;
class ICPTree;

/*
The class does not modify floorplan.icpTree. Thus after
the best ICPTree is found by Simulated Annealing, get the
best ICPTree from the best FloorplanState.
*/
class FloorplanState : public State {
public:
    FloorplanState(Floorplan *floorplan);
    FloorplanState(Floorplan *floorplan, ICPTree *icpTree);
    ~FloorplanState();
    void setFloorplan(Floorplan *floorplan);
    Floorplan *getFloorplan();
    void setICPTree(ICPTree *icpTree);
    ICPTree *getICPTree();
    /*
    @Override
    */
    void doAfterBeingOperated();
    /*
    @Override
    */
    void doBeforeCalculatingCost();
    /*
    @Override
    Copy the ICPTree, but remain the floorplan.
    */
    State *copy();

private:
    Floorplan *floorplan;
    ICPTree *icpTree;
};

#endif