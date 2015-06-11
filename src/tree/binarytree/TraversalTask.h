#ifndef TREE_BINARYTREE_TRAVERSALTASK_H_
#define TREE_BINARYTREE_TRAVERSALTASK_H_

class Node;

class TraversalTask {
public:
    virtual void doWhenTraversing(Node *node) = 0;    
};

#endif