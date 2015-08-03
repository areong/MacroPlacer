#include "tree/icptree/TraversalTaskPlaceNormalMacros.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/contour/Contour.h"
#include "tree/icptree/contour/Edge.h"

TraversalTaskPlaceNormalMacros::TraversalTaskPlaceNormalMacros() {
    packingForward = true;
    exteriorContour = 0;
}

TraversalTaskPlaceNormalMacros::~TraversalTaskPlaceNormalMacros() {

}

void TraversalTaskPlaceNormalMacros::doWhenTraversing(Node *node) {
    if (exteriorContour == 0) {
        return;
    }
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    if (!macroNode->isNormalNode()) {
        return;
    }
    MacroNode *parentMacroNode = dynamic_cast<MacroNode *>(node->getParentNode());
    Edge *parentTopEdge = exteriorContour->getMacroNodeTopEdge(parentMacroNode);
    if (!parentMacroNode->isCovered()) {
        // parentMacroNode.topEdge is in the Contour.
        if (packingForward) {
            // Assume parentMacroNode.topEdge.xStart == parentMacro.xStart.
            if (macroNode->isLeftNode()) {
                exteriorContour->placeMacroOnEdgeWithPackingForward(macroNode, parentTopEdge->getBackEdge());
            } else {
                exteriorContour->placeMacroOnTopOfMacroWithPackingForward(macroNode, parentMacroNode);
            }
        } else {
            // Assume parentMacroNode.topEdge.xEnd == parentMacro.xEnd.
            if (macroNode->isLeftNode()) {
                exteriorContour->placeMacroOnEdgeWithPackingBackward(macroNode, parentTopEdge->getFrontEdge());
            } else {
                exteriorContour->placeMacroOnTopOfMacroWithPackingBackward(macroNode, parentMacroNode);
            }
        }
    } else {
        // parentMacroNode.topEdge is not in the Contour.
        Macro *parentMacro = parentMacroNode->getMacro();
        int parentMacroXStart = exteriorContour->getMacroXStart(parentMacro);
        int parentMacroXEnd = exteriorContour->getMacroXEnd(parentMacro);
        if (packingForward) {
            if (macroNode->isLeftNode()) {
                exteriorContour->placeMacroAtXWithPackingForward(macroNode, parentMacroXEnd);
            } else {
                exteriorContour->placeMacroAtXWithPackingForward(macroNode, parentMacroXStart);
            }
        } else {
            if (macroNode->isLeftNode()) {
                exteriorContour->placeMacroAtXWithPackingBackward(macroNode, parentMacroXStart);
            } else {
                exteriorContour->placeMacroAtXWithPackingBackward(macroNode, parentMacroXEnd);
            }
        }
    }
}

void TraversalTaskPlaceNormalMacros::setPackingForward(bool forward) {
    packingForward = forward;
}

void TraversalTaskPlaceNormalMacros::setExteriorContour(Contour *contour) {
    exteriorContour = contour;
}