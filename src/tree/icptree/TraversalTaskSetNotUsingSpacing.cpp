#include "tree/icptree/TraversalTaskSetNotUsingSpacing.h"
#include "tree/icptree/MacroNode.h"

TraversalTaskSetNotUsingSpacing::TraversalTaskSetNotUsingSpacing() {

}

TraversalTaskSetNotUsingSpacing::~TraversalTaskSetNotUsingSpacing() {

}

void TraversalTaskSetNotUsingSpacing::doWhenTraversing(Node *node) {
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    macroNode->useSpacing(false);
}