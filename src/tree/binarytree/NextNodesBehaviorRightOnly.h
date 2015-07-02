#ifndef TREE_BINARYTREE_NEXTNODESBEHAVIORRIGHTONLY_H_
#define TREE_BINARYTREE_NEXTNODESBEHAVIORRIGHTONLY_H_

#include "tree/binarytree/NextNodesBehavior.h"

class NextNodesBehaviorRightOnly : public NextNodesBehavior {
public:
    NextNodesBehaviorRightOnly();
    ~NextNodesBehaviorRightOnly();
    std::vector<Node *> *getNextNodes(Node *node);
    NextNodesBehavior *copy();
};

#endif