#ifndef TREE_BINARYTREE_NEXTNODESBEHAVIORRIGHTFIRST_H_
#define TREE_BINARYTREE_NEXTNODESBEHAVIORRIGHTFIRST_H_

#include "tree/binarytree/NextNodesBehavior.h"

class NextNodesBehaviorRightFirst : public NextNodesBehavior {
public:
    NextNodesBehaviorRightFirst();
    ~NextNodesBehaviorRightFirst();
    std::vector<Node *> *getNextNodes(Node *node);
    NextNodesBehavior *copy();
};

#endif