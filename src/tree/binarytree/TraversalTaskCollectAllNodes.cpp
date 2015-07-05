#include "tree/binarytree/TraversalTaskCollectAllNodes.h"
#include "tree/binarytree/Node.h"

TraversalTaskCollectAllNodes::TraversalTaskCollectAllNodes() {
    nodes = new std::vector<Node *>();
}

TraversalTaskCollectAllNodes::~TraversalTaskCollectAllNodes() {
    delete nodes;
}

void TraversalTaskCollectAllNodes::doWhenTraversing(Node *node) {
    nodes->push_back(node);
}

std::vector<Node *> *TraversalTaskCollectAllNodes::getNodes() {
    return nodes;
}