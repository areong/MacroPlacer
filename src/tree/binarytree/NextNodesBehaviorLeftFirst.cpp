#include "tree/binarytree/NextNodesBehaviorLeftFirst.h"
#include "tree/binarytree/Node.h"

NextNodesBehaviorLeftFirst::NextNodesBehaviorLeftFirst() {

}

NextNodesBehaviorLeftFirst::~NextNodesBehaviorLeftFirst() {

}

std::vector<Node *> *NextNodesBehaviorLeftFirst::getNextNodes(Node *node) {
    std::vector<Node *> *nodes = new std::vector<Node *>();
    if (node->hasLeftNode())
        nodes->push_back(node->getLeftNode());
    if (node->hasRightNode())
        nodes->push_back(node->getRightNode());
    return nodes;
}

NextNodesBehavior *NextNodesBehaviorLeftFirst::copy() {
    return new NextNodesBehaviorLeftFirst();
}