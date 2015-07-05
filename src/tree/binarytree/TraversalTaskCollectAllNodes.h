#ifndef TREE_BINARYTREE_TRAVERSALTASKCOLLECTALLNODES_H_
#define TREE_BINARYTREE_TRAVERSALTASKCOLLECTALLNODES_H_

#include "tree/binarytree/TraversalTask.h"
#include <vector>

/*
Used in BinaryTree::~BinaryTree().
Assume each Node is traversed only once as in BinaryTree.traverseDfs().
*/
class TraversalTaskCollectAllNodes : public TraversalTask {
public:
    TraversalTaskCollectAllNodes();
    ~TraversalTaskCollectAllNodes();
    void doWhenTraversing(Node *node);
    std::vector<Node *> *getNodes();

private:
    std::vector<Node *> *nodes;
};

#endif