#include "tree/binarytree/NextNodesBehaviorRightOnly.h"
#include "tree/binarytree/Node.h"

NextNodesBehaviorRightOnly::NextNodesBehaviorRightOnly() {

}

NextNodesBehaviorRightOnly::~NextNodesBehaviorRightOnly() {

}

std::vector<Node *> *NextNodesBehaviorRightOnly::getNextNodes(Node *node) {
    std::vector<Node *> *nodes = new std::vector<Node *>();
    if (node->hasRightNode())
        nodes->push_back(node->getRightNode());
    return nodes;
}

NextNodesBehavior *NextNodesBehaviorRightOnly::copy() {
    return new NextNodesBehaviorRightOnly();
}