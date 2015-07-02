#include "tree/icptree/TraversalTaskPrintIdAndIdentity.h"
#include <iostream>
#include "tree/icptree/MacroNode.h"

TraversalTaskPrintIdAndIdentity::TraversalTaskPrintIdAndIdentity() {

}

TraversalTaskPrintIdAndIdentity::~TraversalTaskPrintIdAndIdentity() {

}

void TraversalTaskPrintIdAndIdentity::doWhenTraversing(Node *node) {
    std::cout << node->getId();
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    switch (macroNode->getIdentity()) {
        case MacroNode::NORMAL_NODE:
            std::cout << "n ";
            break;
        case MacroNode::BRANCH_NODE:
            std::cout << "b ";
            break;
        case MacroNode::SWITCH_NODE:
            std::cout << "s ";
            break;
        case MacroNode::CORNER_NODE:
            std::cout << "c ";
            break;
        default:
            std::cout << "n ";
            break;
    }
}