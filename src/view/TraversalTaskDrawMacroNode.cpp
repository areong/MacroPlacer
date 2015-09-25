#include "view/TraversalTaskDrawMacroNode.h"
#include "model/Macro.h"
#include "tree/icptree/MacroNode.h"
#include "view/MacroView.h"
#include "view/Window.h"

TraversalTaskDrawMacroNode::TraversalTaskDrawMacroNode(Window *window) {
    this->window = window;
}

TraversalTaskDrawMacroNode::~TraversalTaskDrawMacroNode() {

}

void TraversalTaskDrawMacroNode::doWhenTraversing(Node *node) {
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    Macro *macro = macroNode->getMacro();
    MacroView *macroView = new MacroView(window, macro);
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
    // Draw lines between the Node and its children.
    MacroNode *leftMacroNode = dynamic_cast<MacroNode *>(macroNode->getLeftNode());
    MacroNode *rightMacroNode = dynamic_cast<MacroNode *>(macroNode->getRightNode());
    float macroXCenter = (macro->getXStart() + macro->getXEnd()) / 2;
    float macroYCenter = (macro->getYStart() + macro->getYEnd()) / 2;
    if (leftMacroNode != 0) {
        Macro *leftMacro = leftMacroNode->getMacro();
        float leftMacroXCenter = (leftMacro->getXStart() + leftMacro->getXEnd()) / 2;
        float leftMacroYCenter = (leftMacro->getYStart() + leftMacro->getYEnd()) / 2;
        float leftLineColor[] = {1, 0.6, 0.6};
        window->drawLine(macroXCenter, macroYCenter,
            leftMacroXCenter, leftMacroYCenter,
            leftLineColor[0], leftLineColor[1], leftLineColor[2]);
    }
    if (rightMacroNode != 0) {
        Macro *rightMacro = rightMacroNode->getMacro();
        float rightMacroXCenter = (rightMacro->getXStart() + rightMacro->getXEnd()) / 2;
        float rightMacroYCenter = (rightMacro->getYStart() + rightMacro->getYEnd()) / 2;
        float rightLineColor[] = {0.6, 0.6, 1};
        window->drawLine(macroXCenter, macroYCenter,
            rightMacroXCenter, rightMacroYCenter,
            rightLineColor[0], rightLineColor[1], rightLineColor[2]);
    }
}
