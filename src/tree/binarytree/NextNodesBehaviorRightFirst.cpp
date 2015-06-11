#include "tree/binarytree/NextNodesBehaviorRightFirst.h"
#include "tree/binarytree/Node.h"

NextNodesBehaviorRightFirst::NextNodesBehaviorRightFirst() {

}

NextNodesBehaviorRightFirst::~NextNodesBehaviorRightFirst() {

}

std::vector<Node *> *NextNodesBehaviorRightFirst::getNextNodes(Node *node) {
    std::vector<Node *> *nodes = new std::vector<Node *>();
    if (node->hasRightNode())
        nodes->push_back(node->getRightNode());
    if (node->hasLeftNode())
        nodes->push_back(node->getLeftNode());
    return nodes;
}

NextNodesBehavior *NextNodesBehaviorRightFirst::copy() {
    return new NextNodesBehaviorRightFirst();
}