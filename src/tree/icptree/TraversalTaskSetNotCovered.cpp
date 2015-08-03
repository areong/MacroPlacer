#include "tree/icptree/TraversalTaskSetNotCovered.h"
#include "tree/icptree/MacroNode.h"

TraversalTaskSetNotCovered::TraversalTaskSetNotCovered() {

}

TraversalTaskSetNotCovered::~TraversalTaskSetNotCovered() {

}

void TraversalTaskSetNotCovered::doWhenTraversing(Node *node) {
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    macroNode->setCovered(false);
}