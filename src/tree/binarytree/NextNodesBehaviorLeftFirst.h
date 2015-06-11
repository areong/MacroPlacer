#ifndef TREE_BINARYTREE_NEXTNODESBEHAVIORLEFTFIRST_H_
#define TREE_BINARYTREE_NEXTNODESBEHAVIORLEFTFIRST_H_

#include "tree/binarytree/NextNodesBehavior.h"

class NextNodesBehaviorLeftFirst : public NextNodesBehavior {
public:
    NextNodesBehaviorLeftFirst();
    ~NextNodesBehaviorLeftFirst();
    std::vector<Node *> *getNextNodes(Node *node);
    NextNodesBehavior *copy();
};

#endif