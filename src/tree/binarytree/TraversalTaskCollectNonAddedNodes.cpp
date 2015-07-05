#include "tree/binarytree/TraversalTaskCollectNonAddedNodes.h"
#include "tree/binarytree/Node.h"

TraversalTaskCollectNonAddedNodes::TraversalTaskCollectNonAddedNodes() {
    nodes = new std::vector<Node *>();
}

TraversalTaskCollectNonAddedNodes::~TraversalTaskCollectNonAddedNodes() {
    delete nodes;
}

void TraversalTaskCollectNonAddedNodes::doWhenTraversing(Node *node) {
    if (node->getId() < 0)
        nodes->push_back(node);
}

std::vector<Node *> *TraversalTaskCollectNonAddedNodes::getNodes() {
    return nodes;
}