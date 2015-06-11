#ifndef TREE_BINARYTREE_NEXTNODESBEHAVIOR_H_
#define TREE_BINARYTREE_NEXTNODESBEHAVIOR_H_

#include <vector>

class Node;

class NextNodesBehavior {
public:
    /*
    Remenber to delete the returned vector.
    */
    virtual std::vector<Node *> *getNextNodes(Node *node) = 0;
    /*
    Called by Node.copy().
    */
    virtual NextNodesBehavior *copy() = 0;
};

#endif