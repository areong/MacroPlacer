#ifndef TREE_ICPTREE_TRAVERSALTASKPLACENORMALMACROS_H_
#define TREE_ICPTREE_TRAVERSALTASKPLACENORMALMACROS_H_

#include "tree/binarytree/TraversalTask.h"

class Contour;

/*
Only used with MacroNodes.
*/
class TraversalTaskPlaceNormalMacros : public TraversalTask {
public:
    TraversalTaskPlaceNormalMacros();
    ~TraversalTaskPlaceNormalMacros();
    /*
    @Override
    */
    void doWhenTraversing(Node *node);
    void setPackingForward(bool forward);
    void setExteriorContour(Contour *contour);

private:
    bool packingForward;
    Contour *exteriorContour;
};

#endif