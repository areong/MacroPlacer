#ifndef TREE_ICPTREE_TRAVERSALTASKSETNOTCOVERED_H_
#define TREE_ICPTREE_TRAVERSALTASKSETNOTCOVERED_H_

#include "tree/binarytree/TraversalTask.h"

/*
Only used with MacroNodes.
*/
class TraversalTaskSetNotCovered : public TraversalTask {
public:
    TraversalTaskSetNotCovered();
    ~TraversalTaskSetNotCovered();
    /*
    @Override
    */
    void doWhenTraversing(Node *node);
};

#endif