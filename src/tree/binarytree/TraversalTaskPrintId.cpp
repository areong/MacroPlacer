#include "tree/binarytree/TraversalTaskPrintId.h"
#include <iostream>
#include "tree/binarytree/Node.h"

TraversalTaskPrintId::TraversalTaskPrintId() {

}

TraversalTaskPrintId::~TraversalTaskPrintId() {

}

void TraversalTaskPrintId::doWhenTraversing(Node *node) {
    std::cout << node->_getId() << " ";
}