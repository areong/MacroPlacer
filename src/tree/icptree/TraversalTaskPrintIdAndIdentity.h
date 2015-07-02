#ifndef TREE_ICPTREE_TRAVERSALTASKPRINTIDANDIDENTITY_H_
#define TREE_ICPTREE_TRAVERSALTASKPRINTIDANDIDENTITY_H_

#include "tree/binarytree/TraversalTask.h"

/*
Only used with MacroNodes.
*/
class TraversalTaskPrintIdAndIdentity : public TraversalTask {
public:
    TraversalTaskPrintIdAndIdentity();
    ~TraversalTaskPrintIdAndIdentity();
    void doWhenTraversing(Node *node);
};

#endif