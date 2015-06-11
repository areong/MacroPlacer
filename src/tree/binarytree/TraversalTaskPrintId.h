#ifndef TREE_BINARYTREE_TRAVERSALTASKPRINTID_H_
#define TREE_BINARYTREE_TRAVERSALTASKPRINTID_H_

#include "tree/binarytree/TraversalTask.h"

/*
For testing BinaryTree.
*/
class TraversalTaskPrintId : public TraversalTask {
public:
    TraversalTaskPrintId();
    ~TraversalTaskPrintId();
    void doWhenTraversing(Node *node);
};

#endif