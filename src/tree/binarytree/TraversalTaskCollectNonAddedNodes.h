#ifndef TREE_BINARYTREE_TRAVERSALTASKCOLLECTNONADDEDNODES_H_
#define TREE_BINARYTREE_TRAVERSALTASKCOLLECTNONADDEDNODES_H_

#include "tree/binarytree/TraversalTask.h"
#include <vector>

/*
Used in BinaryTree.copy().
Collect all Nodes which are not added to BinaryTree.nodes,
by checking Node.id. If id < 0 than collect it.
If a non-added Node is setId() manaully than this method might fail.
*/
class TraversalTaskCollectNonAddedNodes : public TraversalTask {
public:
    TraversalTaskCollectNonAddedNodes();
    ~TraversalTaskCollectNonAddedNodes();
    void doWhenTraversing(Node *node);
    std::vector<Node *> *getNodes();

private:
    std::vector<Node *> *nodes;
};

#endif