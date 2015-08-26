#include "view/TraversalTaskDrawMacroNode.h"
#include "tree/icptree/MacroNode.h"
#include "view/MacroView.h"

TraversalTaskDrawMacroNode::TraversalTaskDrawMacroNode(Window *window) {
    this->window = window;
}

TraversalTaskDrawMacroNode::~TraversalTaskDrawMacroNode() {

}

void TraversalTaskDrawMacroNode::doWhenTraversing(Node *node) {
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    MacroView *macroView = new MacroView(window, macroNode->getMacro());
    if (macroNode->isEmptyNode()) {
        macroView->setFillColor(0, 0.1, 0.1);
        macroView->setOutlineColor(0.4, 0.5, 0.5);
    } else {
        switch (macroNode->getIdentity()) {
        case MacroNode::NORMAL_NODE:
            macroView->setFillColor(0.2, 0.4, 0.5);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        case MacroNode::BRANCH_NODE:
            macroView->setFillColor(0.5, 0.6, 0.1);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        case MacroNode::SWITCH_NODE:
            macroView->setFillColor(0.1, 0.8, 0.0);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        case MacroNode::CORNER_NODE:
            macroView->setFillColor(0.8, 0.2, 0.1);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        default:
            macroView->setFillColor(0.2, 0.4, 0.5);
            macroView->setOutlineColor(1, 0.9, 0.9);
        }
    }
    macroView->display();
    delete macroView;
}
