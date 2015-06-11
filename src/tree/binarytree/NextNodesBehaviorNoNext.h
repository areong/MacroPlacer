#ifndef TREE_BINARYTREE_NEXTNODESBEHAVIORNONEXT_H_
#define TREE_BINARYTREE_NEXTNODESBEHAVIORNONEXT_H_

#include "tree/binarytree/NextNodesBehavior.h"

class NextNodesBehaviorNoNext : public NextNodesBehavior {
public:
    NextNodesBehaviorNoNext();
    ~NextNodesBehaviorNoNext();
    std::vector<Node *> *getNextNodes(Node *node);
    NextNodesBehavior *copy();
};

#endif