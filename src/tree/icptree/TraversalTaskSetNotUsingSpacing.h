#ifndef TREE_ICPTREE_TRAVERSALTASKSETNOTUSINGSPACING_H_
#define TREE_ICPTREE_TRAVERSALTASKSETNOTUSINGSPACING_H_

#include "tree/binarytree/TraversalTask.h"

/*
Only used with MacroNodes.
*/
class TraversalTaskSetNotUsingSpacing : public TraversalTask {
public:
    TraversalTaskSetNotUsingSpacing();
    ~TraversalTaskSetNotUsingSpacing();
    /*
    @Override
    */
    void doWhenTraversing(Node *node);
};

#endif