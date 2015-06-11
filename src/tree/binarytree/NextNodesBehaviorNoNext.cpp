#include "tree/binarytree/NextNodesBehaviorNoNext.h"

NextNodesBehaviorNoNext::NextNodesBehaviorNoNext() {

}

NextNodesBehaviorNoNext::~NextNodesBehaviorNoNext() {

}

std::vector<Node *> *NextNodesBehaviorNoNext::getNextNodes(Node *node) {
    std::vector<Node *> *nodes = new std::vector<Node *>();
    return nodes;
}

NextNodesBehavior *NextNodesBehaviorNoNext::copy() {
    return new NextNodesBehaviorNoNext();
}