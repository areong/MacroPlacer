#include "tree/icptree/ICPTree.h"
#include "model/Macro.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/TraversalTaskPlaceNormalMacros.h"
#include "tree/icptree/TraversalTaskSetNotCovered.h"
#include "tree/icptree/TraversalTaskSetNotUsingSpacing.h"
#include "tree/icptree/contour/TopContour.h"
#include "tree/icptree/contour/BottomContour.h"
#include "tree/icptree/contour/RightContour.h"
#include "tree/icptree/contour/LeftContour.h"
#include "utils/Utils.h"

#include <iostream>

ICPTree::ICPTree(std::vector<Macro *> *macros) {
    corner0XStart = 0;
    corner0YStart = 0;
    changeRangeOfEmptyNodeWidth = 10;
    changeRangeOfVerticalDisplacement = 10;
    changeRangeOfSpacing = 10;
    changeRangeOfCorner0Position = 10;
    exteriorTopContour = 0;
    exteriorRightContour = 0;
    exteriorBottomContour = 0;
    exteriorLeftContour = 0;
    interiorBottomContour = 0;
    interiorLeftContour = 0;
    interiorTopContour = 0;
    interiorRightContour = 0;
    maxX = 1;
    minX = 0;
    maxY = 1;
    minY = 0;
    boundingBoxArea = 1;
    interiorRegionArea = 0;

    if (macros != 0) {
        for (int i = 0; i < macros->size(); i++) {
            MacroNode *macroNode = new MacroNode(macros->at(i));
            macroNode->setVerticalDisplacement(0);
            addNode(macroNode);
        }
    }
}

ICPTree::~ICPTree() {
    delete exteriorTopContour;
    delete exteriorRightContour;
    delete exteriorBottomContour;
    delete exteriorLeftContour;
    delete interiorBottomContour;
    delete interiorLeftContour;
    delete interiorTopContour;
    delete interiorRightContour;
}

void ICPTree::initializeRandomly() {
    BinaryTree::initializeRandomly();
    initializeMacroNodesOnBranchesRandomly();
    updateMacroNodesOnBranchesBranchNumber();
}

void ICPTree::initializeMacroNodesOnBranchesRandomly() {
    // Set the root as a CornerNode.
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    root->setAsCornerNode();
    // Traverse left Nodes, set them as BranchNodes,
    // and count the MacroNodes on branches.
    int numNonEmptyMacroNodesOnBranches = 0;
    MacroNode *current = root;
    while (true) {
        numNonEmptyMacroNodesOnBranches += 1;
        if (current->hasLeftNode()) {
            current = dynamic_cast<MacroNode *>(current->getLeftNode());
            current->setAsBranchNode();
        } else {
            break;
        }
    }
    // If numNonEmptyMacroNodesOnBranches is less then four,
    // select enough not-on-branch MacroNodes, or NormalNodes, and insert at
    // current as leftNodes, and set all MacroNodes on branches as CornerNodes.
    if (numNonEmptyMacroNodesOnBranches < 4) {
        for (int i = numNonEmptyMacroNodesOnBranches; i < 4; i++) {
            MacroNode *selectedNormalNode = dynamic_cast<MacroNode *>(getNodeRandomly());
            if (!selectedNormalNode->isNormalNode()) {
                selectedNormalNode = dynamic_cast<MacroNode *>(getNodeRandomly());
            }
            removeNode(selectedNormalNode, false);
            insertLeftNode(selectedNormalNode, current);
        }
        current = dynamic_cast<MacroNode *>(root->getLeftNode());
        for (int i = 1; i < 4; i++) {
            current->setAsCornerNode();
            current = dynamic_cast<MacroNode *>(current->getLeftNode());
        }
    } else {
        // There are 3 or more leftNodes (excluding root).
        // Select three Nodes and set as CornerNodes.
        std::vector<int> *iths = Utils::randints(1, numNonEmptyMacroNodesOnBranches, 3);
        current = dynamic_cast<MacroNode *>(root->getLeftNode());
        int whichIth = 0;
        for (int i = 1; i < numNonEmptyMacroNodesOnBranches; i++) {
            if (whichIth < 3 && i == iths->at(whichIth)) {
                current->setAsCornerNode();
                whichIth += 1;
            }
            current = dynamic_cast<MacroNode *>(current->getLeftNode());
        }
        delete iths;   
    }
}

void ICPTree::insertLeftNode(Node *node, Node *position) {
    BinaryTree::insertLeftNode(node, position);
    // Set idenitiy.
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    MacroNode *macroNodePosition = dynamic_cast<MacroNode *>(position);
    if (macroNode != 0 && macroNodePosition != 0) { // BinaryTree uses this method with Node.
        switch (macroNodePosition->getIdentity()) {
            case MacroNode::NORMAL_NODE:
                macroNode->setAsNormalNode();
                break;
            case MacroNode::BRANCH_NODE:
                macroNode->setAsBranchNode();
                break;
            case MacroNode::SWITCH_NODE:
                macroNode->setAsBranchNode();
                break;
            case MacroNode::CORNER_NODE:
                macroNode->setAsBranchNode();
                break;
            default:
                macroNode->setAsNormalNode();
                break;
        }
    }
}

void ICPTree::insertRightNode(Node *node, Node *position) {
    BinaryTree::insertRightNode(node, position);
    // Set as a Normal Node.
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    if (macroNode != 0)   // BinaryTree uses this method with Node.
        macroNode->setAsNormalNode();
}

bool ICPTree::removeNode(Node *node, bool replaceWithLeftNode) {
    MacroNode *macroNode = dynamic_cast<MacroNode *>(node);
    if (macroNode->isCornerNode()) {
        // If it is root, only can replaceWithLeftNode.
        if (node == getRoot()) {
            MacroNode *macroNodeLeft = dynamic_cast<MacroNode *>(node->getLeftNode());
            if (!replaceWithLeftNode) {
                return false;
            } else if (macroNodeLeft->isEmptyNode()) {
                return false;
            } else if (!moveCorner(macroNode, false)) {
                return false;
            }
        } else {
            // Try to move the CornerNode.
            if (!moveCorner(macroNode, true)) {
                if (!moveCorner(macroNode, false)) {
                    return false;
                }
            }
        }
        MacroNode *leftMostNode = getLeftMostMacroNode();
        if (leftMostNode->isCornerNode() && leftMostNode->hasRightNode()) {
            return false;
        }
    }
    if (macroNode->isBranchNode()) {
        MacroNode *leftMostNode = getLeftMostMacroNode();
        if (leftMostNode->isCornerNode() && leftMostNode->hasRightNode()) {
            return false;
        }
    }
    // If the node can be removed, remove it.
    return BinaryTree::removeNode(node, replaceWithLeftNode);
}

void ICPTree::swapNodes(Node *node1, Node *node2) {
    BinaryTree::swapNodes(node1, node2);
    // Exchange identity.
    MacroNode *macroNode1 = dynamic_cast<MacroNode *>(node1);
    MacroNode *macroNode2 = dynamic_cast<MacroNode *>(node2);
    if (macroNode1 != 0 && macroNode2 != 0) {   // BinaryTree uses this method with Node.
        bool toSwapIdentity = false;
        if (macroNode1->isNormalNode() || macroNode2->isNormalNode()) {
            toSwapIdentity = true;
        } else if (macroNode1->getLeftNode() != macroNode2 && macroNode2->getLeftNode() != macroNode1) {
            toSwapIdentity = true;
        }
        if (toSwapIdentity) {
            swapMacroNodesIdentity(macroNode1, macroNode2);
            int verticalDisplacement1 = macroNode1->getVerticalDisplacement();
            macroNode1->setVerticalDisplacement(macroNode2->getVerticalDisplacement());
            macroNode2->setVerticalDisplacement(verticalDisplacement1);
        }
    }
}

int ICPTree::setCorner0Position(int x, int y) {
    corner0XStart = x;
    corner0YStart = y;
}

MacroNode *ICPTree::getCornerNode(int ith) {
    int count = 0;
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        if (current->isCornerNode()) {
            if (count == ith)
                return current;
            count += 1;
        }
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
    return 0;
}

std::vector<MacroNode *> *ICPTree::getCornerNodes() {
    std::vector<MacroNode *> *results = new std::vector<MacroNode *>();
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        if (current->isCornerNode()) {
            results->push_back(current);
            if (results->size() == 4)
                break;
        }
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
    return results;
}

MacroNode *ICPTree::getNonEmptyBranchNodeRandomly() {
    std::vector<MacroNode *> *nonEmptyBranchNodes = new std::vector<MacroNode *>();
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        if (current->isBranchNode() && !current->isEmptyNode())
            nonEmptyBranchNodes->push_back(current);
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
    MacroNode *result = 0;
    if (nonEmptyBranchNodes->size() > 0)
        result = nonEmptyBranchNodes->at(Utils::randint(0, nonEmptyBranchNodes->size()));
    delete nonEmptyBranchNodes;
    return result;
}

MacroNode *ICPTree::getNonEmptyMacroNodeOnBranchesRandomly() {
    std::vector<MacroNode *> *nonEmptyMacroNodes = new std::vector<MacroNode *>();
    MacroNode *current = dynamic_cast<MacroNode *>(getRoot()->getLeftNode()); // Exclude corner 0.
    while (current != 0) {
        if (!current->isEmptyNode())
            nonEmptyMacroNodes->push_back(current);
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
    MacroNode *result = 0;
    if (nonEmptyMacroNodes->size() > 0)
        result = nonEmptyMacroNodes->at(Utils::randint(0, nonEmptyMacroNodes->size()));
    delete nonEmptyMacroNodes;
    return result;
}

MacroNode *ICPTree::getSwitchNodeRandomly() {
    std::vector<MacroNode *> *switchNodes = new std::vector<MacroNode *>();
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        if (current->isSwitchNode())
            switchNodes->push_back(current);
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
    MacroNode *result = 0;
    if (switchNodes->size() > 0)
        result = switchNodes->at(Utils::randint(0, switchNodes->size()));
    delete switchNodes;
    return result;
}

MacroNode *ICPTree::getEmptyNodeInsertableMacroNodeRandomly() {
    std::vector<MacroNode *> *candidateNodes = new std::vector<MacroNode *>();
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        MacroNode *currentLeftNode = dynamic_cast<MacroNode *>(current->getLeftNode());
        if (!current->isEmptyNode()) {
            if (currentLeftNode != 0)
                if (!currentLeftNode->isEmptyNode())
                    candidateNodes->push_back(current);
        }
        current = currentLeftNode;
    }
    MacroNode *result = 0;
    if (candidateNodes->size() > 0)
        result = candidateNodes->at(Utils::randint(0, candidateNodes->size()));
    delete candidateNodes;
    return result;
}

std::vector<MacroNode *> *ICPTree::getEmptyNodes() {
    std::vector<MacroNode *> *emptyNodes = new std::vector<MacroNode *>();
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        if (current->isEmptyNode())
            emptyNodes->push_back(current);
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
    return emptyNodes;
}

MacroNode *ICPTree::getEmptyNodeRandomly() {
    std::vector<MacroNode *> *emptyNodes = getEmptyNodes();
    MacroNode *result = 0;
    if (emptyNodes->size() > 0)
        result = emptyNodes->at(Utils::randint(0, emptyNodes->size()));
    delete emptyNodes;
    return result;
}

bool ICPTree::moveCorner(int ith, bool forward) {
    return moveCorner(getCornerNode(ith), forward);
}

bool ICPTree::moveCorner(MacroNode *cornerNode, bool forward) {
    // Forward
    // C-C: do nothing.
    // B-C: set B Corner, set C Branch.
    // S-C: set S Corner, set C Branch.
    // Backward
    // C-C: do nothing.
    // C-B: set B Corner, set C Branch.
    // C-S: set S Corner, set C Branch.
    MacroNode *targetNode;
    if (forward)
        targetNode = dynamic_cast<MacroNode *>(cornerNode->getParentNode());   // Always exists.
    else
        targetNode = dynamic_cast<MacroNode *>(cornerNode->getLeftNode());     // Might not exists.
    if (targetNode == 0)
        return false;
    else if (targetNode->isCornerNode())
        return false;
    cornerNode->setAsBranchNode();
    targetNode->setAsCornerNode();
    return true;
}

bool ICPTree::moveCornerRandomly() {
    return moveCorner(Utils::randint(1, 4), Utils::randbool());
}

void ICPTree::assignSwitch(MacroNode *node) {
    node->setAsSwitchNode();
}

void ICPTree::assignSwitchRandomly() {
    MacroNode *node = getNonEmptyBranchNodeRandomly();
    if (node != 0)
        assignSwitch(node);
}

bool ICPTree::moveSwitch(MacroNode *node, bool forward) {
    MacroNode *target = node;
    if (forward) {
        while (true) {
            target = dynamic_cast<MacroNode *>(target->getParentNode());
            if (target->isSwitchNode() || target->isCornerNode())
                return false;
            else if (target->isEmptyNode()) {
                continue;  // Skip a empty BranchNode.
            } else {
                break;  // Found a non-empty BranchNode.
            }
        }
    } else {
        while (true) {
            target = dynamic_cast<MacroNode *>(target->getLeftNode());
            if (target == 0)
                return false;
            if (target->isSwitchNode() || target->isCornerNode())
                return false;
            else if (target->isEmptyNode()) {
                continue;  // Skip a empty BranchNode.
            } else {
                break;  // Found a non-empty BranchNode.
            }
        }
    }
    node->setAsBranchNode();
    target->setAsSwitchNode();
    return true;
}

bool ICPTree::moveSwitchRandomly() {
    MacroNode *node = getSwitchNodeRandomly();
    if (node != 0)
        return moveSwitch(node, Utils::randbool());
    else
        return false;
}

void ICPTree::removeSwitch(MacroNode *node) {
    node->setAsBranchNode();
}

void ICPTree::removeSwitchRandomly() {
    MacroNode *node = getSwitchNodeRandomly();
    if (node != 0)
        removeSwitch(node);
}

void ICPTree::insertEmptyNode(MacroNode *position) {
    insertLeftNode(MacroNode::createEmptyNode(position), position);
}

void ICPTree::insertEmptyNodeRandomly() {
    MacroNode *node = getEmptyNodeInsertableMacroNodeRandomly();
    if (node != 0)
        insertEmptyNode(node);
}

bool ICPTree::removeEmptyNode(MacroNode *node) {
    // First check whether the node is a CornerNode.
    // If true, move the CornerNode forward or backward
    // by checking whether the leftNode exists and is not a CornerNode.
    // If true, move backward; else move forward.
    // If move successfully, remove the node.
    bool moveCornerSuccessfully = true;
    if (node->isCornerNode()) {
        int ith = getWhichCornerNodeIs(node);  // Can only be 1, 2 or 3
        bool forward = true;
        if (node->hasLeftNode())
            if (!dynamic_cast<MacroNode *>(node->getLeftNode())->isCornerNode())
                forward = false;
        moveCornerSuccessfully = moveCorner(ith, forward);
    }
    if (moveCornerSuccessfully) {
        // Remove the empty Node by removeNode() since empty Nodes can have
        // right Nodes caused by removing MacroNodes on branches.
        removeNode(node, true);
        //// Do not need removeNode() because an empty Node does not have
        //// right Node.
        //Node *parent = node->getParentNode();
        //Node *leftNode = node->getLeftNode();
        //parent->setLeftNode(leftNode);
        //if (leftNode != 0)
        //    leftNode->setParentNode(parent);
        delete node;
        return true;
    } else {
        return false;
    }
}

bool ICPTree::removeEmptyNodeRandomly() {
    MacroNode *node = getEmptyNodeRandomly();
    if (node != 0)
        return removeEmptyNode(node);
    else
        return false;
}

void ICPTree::setChangeRangeOfEmptyNodeWidth(int changeRange) {
    changeRangeOfEmptyNodeWidth = changeRange;
}

void ICPTree::setChangeRangeOfVerticalDisplacement(int changeRange) {
    changeRangeOfVerticalDisplacement = changeRange;
}

void ICPTree::setChangeRangeOfSpacing(int changeRange) {
    changeRangeOfSpacing = changeRange;
}

void ICPTree::setChangeRangeOfCorner0Position(int changeRange) {
    changeRangeOfCorner0Position = changeRange;
}

void ICPTree::changeRandomEmptyNodeWidthRandomly() {
    MacroNode *emptyNode = getEmptyNodeRandomly();
    if (emptyNode == 0) {
        return;
    }
    int width = emptyNode->getMacroWidthByBranchNumber();
    int maxWidth = width + changeRangeOfEmptyNodeWidth;
    int minWidth = width - changeRangeOfEmptyNodeWidth;
    if (minWidth < 1) {
        minWidth = 1;
    }
    int newWidth = Utils::randint(minWidth, maxWidth + 1);
    emptyNode->setMacroWidthByBranchNumber(newWidth);
}

void ICPTree::changeRandomMacroNodeVerticalDisplacementRandomly() {
    MacroNode *macroNode = getNonEmptyMacroNodeOnBranchesRandomly();
    if (macroNode == 0) {
        return;
    }
    int verticalDisplacement = macroNode->getVerticalDisplacement();
    verticalDisplacement += Utils::randint(-1 * changeRangeOfVerticalDisplacement, changeRangeOfVerticalDisplacement + 1);
    macroNode->setVerticalDisplacement(verticalDisplacement);
    // Update leftNode if the leftNode is an empty Node.
    if (macroNode->hasLeftNode()) {
        MacroNode *leftNode = dynamic_cast<MacroNode *>(macroNode->getLeftNode());
        if (leftNode->isEmptyNode()) {
            if (macroNode->isCornerNode()) {
                leftNode->setVerticalDisplacement(0);
            } else {
                leftNode->setVerticalDisplacement(verticalDisplacement);
            }
        }
    }
}

void ICPTree::changeRandomMacroNodeSpacingRandomly() {
    MacroNode *macroNode = getNonEmptyMacroNodeOnBranchesRandomly();
    int spacing = macroNode->getSpacing();
    spacing += Utils::randint(-1 * changeRangeOfSpacing, changeRangeOfSpacing + 1);
    if (spacing < 0) {
        spacing = 0;
    }
    macroNode->setSpacing(spacing);
}

void ICPTree::changeCorner0PositionRandomly() {
    corner0XStart += Utils::randint(-1 * changeRangeOfCorner0Position, changeRangeOfCorner0Position + 1);
    corner0YStart += Utils::randint(-1 * changeRangeOfCorner0Position, changeRangeOfCorner0Position + 1);
}

void ICPTree::rotateRandomMacroRandomly() {

}


void ICPTree::traverseAll(TraversalTask *task) {
    // The packing direction might have changed.
    updatePackingDirectionOfMacroNodesOnBranches();
    // First, push all CornerNodes and SwitchNodes into a vector.
    // Push root first.
    std::vector<MacroNode *> *starts = new std::vector<MacroNode *>();
    MacroNode *current = dynamic_cast<MacroNode *>(getRoot());
    while (true) {
        if (current->isCornerNode() || current->isSwitchNode())
            starts->push_back(current);
        if (current->hasLeftNode())
            current = dynamic_cast<MacroNode *>(current->getLeftNode());
        else
            break;
    }
    // For each MacroNode in starts, traverse the tree from the MacroNode's
    // leftNode (if it has leftNode). Start from the last in starts.
    for (int i = starts->size() - 1; i >= 0; i--) {
        MacroNode *start = starts->at(i);
        if (start->hasLeftNode())
            traverseDfs(starts->at(i)->getLeftNode(), task);
    }
    // Traverse corner 0.
    traverseDfs(getRoot(), task);
    delete starts;
}

void ICPTree::placeMacrosAssumingNoSwitch() {
    // Create Contours.
    createContours();
    // Set all MacroNodes not covered.
    setAllMacroNodesNotCovered();
    // Merge contiguous empty Nodes.
    updateMacroNodesOnBranchesBranchNumber();
    //mergeContiguousEmptyBranchNodes();
    // Set spacing.
    setAllMacroNodesNotUsingSpacing();
    setMacroNodesOnBranchesSpacingDirection();
    // Place Macros on branches.
    // TopContour
    exteriorTopContour->initialize(corner0XStart, corner0YStart);
    interiorBottomContour->initialize(corner0XStart, corner0YStart);
    std::vector<MacroNode *> *cornerNodes = getCornerNodes();
    MacroNode *currentNode = dynamic_cast<MacroNode *>(cornerNodes->at(0)->getLeftNode());
    exteriorTopContour->placeMacroOnEdgeWithPackingForward(cornerNodes->at(0), exteriorTopContour->getTail());
    interiorBottomContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(cornerNodes->at(0));
    while (true) {
        exteriorTopContour->placeMacroOnTailByVerticalDisplacementWithPackingForward(currentNode);
        interiorBottomContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(currentNode);
        if (currentNode->isCornerNode()) {
            break;
        }
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    }
    exteriorTopContour->setTailYToTheLastMacroYStart();
    // RightContour
    Macro *corner1Macro = currentNode->getMacro();
    int corner1XStart = exteriorRightContour->getMacroYStart(corner1Macro);
    int corner1YStart = exteriorRightContour->getMacroXEnd(corner1Macro);
    corner1YStart -= currentNode->getSpacing();
    exteriorRightContour->initialize(corner1XStart, corner1YStart);
    interiorLeftContour->initialize(corner1XStart, corner1YStart);
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    while (true) {
        exteriorRightContour->placeMacroOnTailByVerticalDisplacementWithPackingForward(currentNode);
        interiorLeftContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(currentNode);
        if (currentNode->isCornerNode()) {
            break;
        }
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    }
    // Legalize interiorLeftContour.
    interiorLeftContour->legalizeMacrosToALeftContour(interiorBottomContour);
    exteriorRightContour->setTailYToTheLastMacroYStart();
    interiorLeftContour->calculateMaxY(); // maxY may change after legalization.
    exteriorRightContour->calculateMaxY();
    // BottomContour
    Macro *corner2Macro = currentNode->getMacro();
    int corner2XStart = exteriorBottomContour->getMacroXEnd(corner2Macro);
    int corner2YEnd = exteriorBottomContour->getMacroYStart(corner2Macro);
    corner2XStart -= currentNode->getSpacing();
    exteriorBottomContour->initialize(corner2XStart, corner2YEnd);
    interiorTopContour->initialize(corner2XStart, corner2YEnd);
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    while (true) {
        exteriorBottomContour->placeMacroOnTailByVerticalDisplacementWithPackingForward(currentNode);
        interiorTopContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(currentNode);
        if (currentNode->isCornerNode()) {
            break;
        }
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    }
    // Legalize interiorTopContour.
    interiorTopContour->legalizeMacrosToALeftContour(interiorLeftContour);
    interiorTopContour->legalizeMacrosToABottomContour(interiorBottomContour);
    exteriorBottomContour->setTailYToTheLastMacroYStart();
    interiorTopContour->calculateMaxY(); // maxY may change after legalization.
    exteriorBottomContour->calculateMaxY();
    // LeftContour
    Macro *corner3Macro = currentNode->getMacro();
    int corner3XEnd = exteriorLeftContour->getMacroYStart(corner3Macro);
    int corner3YEnd = exteriorLeftContour->getMacroXEnd(corner3Macro);
    corner3YEnd += currentNode->getSpacing();
    exteriorLeftContour->initialize(corner3XEnd, corner3YEnd);
    interiorRightContour->initialize(corner3XEnd, corner3YEnd);
    // Check if corner 3 has any leftNode. If there are only four Macros
    // on branches, corner 3 will have no leftNode.
    if (currentNode->hasLeftNode()) {
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        while (true) {
            exteriorLeftContour->placeMacroOnTailByVerticalDisplacementWithPackingForward(currentNode);
            interiorRightContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(currentNode);
            if (!currentNode->hasLeftNode()) {  // No more CornerNode
                break;
            }
            currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        }
        // Legalize interiorRightContour.
        interiorRightContour->legalizeMacrosToARightContour(interiorBottomContour);
        interiorRightContour->legalizeMacrosToALeftContour(interiorTopContour);
        interiorRightContour->legalizeMacrosToABottomContour(interiorLeftContour);
        interiorRightContour->calculateMaxY(); // maxY may change after legalization.
        exteriorLeftContour->calculateMaxY();
    }
    // Legalize exteriorLeftContour.tail to corner0.xStart.
    if (exteriorLeftContour->getEdgeYEnd(exteriorLeftContour->getTail()) > corner0XStart) {
        exteriorLeftContour->setEdgeYEnd(exteriorLeftContour->getTail(), corner0XStart);
        interiorRightContour->setEdgeYEnd(interiorRightContour->getHead(), corner0XStart);
    }
    // Place Normal Macros.
    TraversalTaskPlaceNormalMacros *task = new TraversalTaskPlaceNormalMacros();
    task->setPackingForward(true);
    // Left
    task->setExteriorContour(exteriorLeftContour);
    if (cornerNodes->at(3)->hasLeftNode()) {
        traverseDfs(cornerNodes->at(3)->getLeftNode(), task);
    }
    // Bottom
    task->setExteriorContour(exteriorBottomContour);
    if (cornerNodes->at(2)->hasLeftNode()) {
        traverseDfs(cornerNodes->at(2)->getLeftNode(), task);
    }
    // Right
    task->setExteriorContour(exteriorRightContour);
    if (cornerNodes->at(1)->hasLeftNode()) {
        traverseDfs(cornerNodes->at(1)->getLeftNode(), task);
    }
    // Top
    task->setExteriorContour(exteriorTopContour);
    if (cornerNodes->at(0)->hasLeftNode()) {
        traverseDfs(cornerNodes->at(0)->getLeftNode(), task);
    }
    // Corner 0
    traverseDfs(cornerNodes->at(0), task);
    delete cornerNodes;
    delete task;
    // Calculate max min x y and interior region area.
    calculateMaxMinXYAssumingNoSwitch();
    calculateBoundingBoxArea();
    calculateInteriorRegionArea();
}

int ICPTree::getMaxX() {
    return maxX;
}

int ICPTree::getMinX() {
    return minX;
}

int ICPTree::getMaxY() {
    return maxY;
}

int ICPTree::getMinY() {
    return minY;
}

int ICPTree::getBoundingBoxArea() {
    return boundingBoxArea;
}

int ICPTree::getInteriorRegionArea() {
    return interiorRegionArea;
}

int ICPTree::getBoundingBoxAspectRatio() {
    return (double) (maxY - minY) / (double) (maxX - minX);
}

BinaryTree *ICPTree::createBinaryTree() {
    return new ICPTree();
}

BinaryTree *ICPTree::copy() {
    ICPTree *icpTree = dynamic_cast<ICPTree *>(BinaryTree::copy());
    icpTree->setCorner0Position(corner0XStart, corner0YStart);
    icpTree->setChangeRangeOfCorner0Position(changeRangeOfCorner0Position);
    icpTree->setChangeRangeOfVerticalDisplacement(changeRangeOfVerticalDisplacement);
    icpTree->setChangeRangeOfEmptyNodeWidth(changeRangeOfEmptyNodeWidth);
    return icpTree;
}

void ICPTree::swapMacroNodesIdentity(MacroNode *node1, MacroNode *node2) {
    MacroNode::Identity node1Identity = node1->getIdentity();
    node1->setIdentity(node2->getIdentity());
    node2->setIdentity(node1Identity);
}

void ICPTree::swapMacroNodesPackingDirection(MacroNode *node1, MacroNode *node2) {
    bool node1PackingDirection = node1->isPackingForward();
    node1->setPackingDirection(node2->isPackingForward());
    node2->setPackingDirection(node1PackingDirection);
}

MacroNode *ICPTree::getLeftMostMacroNode() {
    MacroNode *macroNode = dynamic_cast<MacroNode *>(getRoot());
    while (macroNode->hasLeftNode()) {
        macroNode = dynamic_cast<MacroNode *>(macroNode->getLeftNode());
    }
    return macroNode;
}

int ICPTree::getWhichCornerNodeIs(MacroNode *node) {
    std::vector<MacroNode *> *cornerNodes = getCornerNodes();
    int ith = -1;
    for (int i = 0; i < 4; i++) {
        if (node == cornerNodes->at(i)) {
            ith = i;
            break;
        }
    }
    delete cornerNodes;
    return ith;
}

void ICPTree::updatePackingDirectionOfMacroNodesOnBranches() {
    bool packingForward = true;
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        current->setPackingDirection(packingForward);
        if (current->isCornerNode())
            packingForward = true;
        else if (current->isSwitchNode())
            packingForward ^= true;
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
}

void ICPTree::createContours() {
    delete exteriorTopContour;
    delete exteriorRightContour;
    delete exteriorBottomContour;
    delete exteriorLeftContour;
    delete interiorBottomContour;
    delete interiorLeftContour;
    delete interiorTopContour;
    delete interiorRightContour;
    exteriorTopContour = new TopContour();
    exteriorRightContour = new RightContour();
    exteriorBottomContour = new BottomContour();
    exteriorLeftContour = new LeftContour();
    interiorBottomContour = new BottomContour();
    interiorLeftContour = new LeftContour();
    interiorTopContour = new TopContour();
    interiorRightContour = new RightContour();
}

void ICPTree::updateMacroNodesOnBranchesBranchNumber() {
    MacroNode *currentNode = dynamic_cast<MacroNode *>(getRoot());
    MacroNode::BranchNumber branchNumber = MacroNode::TOP_BRANCH;
    currentNode->setBranchNumber(branchNumber); // Corner 0 is on the top branch.
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    while (true) {
        currentNode->setBranchNumber(branchNumber);
        if (currentNode->isCornerNode()) {
            branchNumber = MacroNode::getNextBranchNumber(branchNumber);
        }
        if (currentNode->hasLeftNode()) {
            currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        } else {
            break;
        }
    }
}

void ICPTree::mergeContiguousEmptyBranchNodes() {
    std::vector<MacroNode *> *emptyNodes = getEmptyNodes();
    if (emptyNodes->size() == 0) {
        delete emptyNodes;
        return;
    }
    int reservedNodeIth = 0;
    MacroNode *reservedNode;
    int totalWidth = emptyNodes->at(reservedNodeIth)->getMacroWidthByBranchNumber();
    MacroNode *currentNode;
    MacroNode *previousNode;
    for (int i = 1; i < emptyNodes->size(); i++) {
        currentNode = emptyNodes->at(i);
        previousNode = emptyNodes->at(i - 1);
        if (currentNode->isCornerNode()) {
            continue;
        }
        if (previousNode->getLeftNode() == currentNode) {
            totalWidth += currentNode->getMacroWidthByBranchNumber();
        } else {
            if (i > reservedNodeIth + 1) {
                // Set reservedNode.macro's width.
                reservedNode = emptyNodes->at(reservedNodeIth);
                reservedNode->setMacroWidthByBranchNumber(totalWidth);
                // Remove empty Nodes.
                // Do not use BinaryTree.removeNode()
                // because an empty Node has no rightNode.
                Node *theNodeAfterContiguousEmptyNodes = previousNode->getLeftNode();
                reservedNode->setLeftNode(theNodeAfterContiguousEmptyNodes);
                theNodeAfterContiguousEmptyNodes->setParentNode(reservedNode);
                for (int j = reservedNodeIth + 1; j < i; j++) {    
                    delete emptyNodes->at(j);
                }
            }
            reservedNodeIth = i;
            totalWidth = currentNode->getMacroWidthByBranchNumber();
        }
    }
    delete emptyNodes;
}

void ICPTree::setAllMacroNodesNotCovered() {
    TraversalTask *task = new TraversalTaskSetNotCovered();
    traverseAll(task);
    delete task;
}

void ICPTree::setAllMacroNodesNotUsingSpacing() {
    TraversalTask *task = new TraversalTaskSetNotUsingSpacing();
    traverseAll(task);
    delete task;
}

void ICPTree::setMacroNodesOnBranchesSpacingDirection() {
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    root->useSpacing(true);
    root->setSpacingDirection(1);
    MacroNode *currentNode = dynamic_cast<MacroNode *>(root->getLeftNode());
    while (true) {
        if (currentNode->isCornerNode()) {
            break;
        }
        currentNode->useSpacing(true);
        currentNode->setSpacingDirection(1);
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    }
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    while (true) {
        if (currentNode->isCornerNode()) {
            break;
        }
        currentNode->useSpacing(true);
        currentNode->setSpacingDirection(2);
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    }
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    while (true) {
        if (currentNode->isCornerNode()) {
            break;
        }
        currentNode->useSpacing(true);
        currentNode->setSpacingDirection(3);
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    }
    if (currentNode->hasLeftNode()) {
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        while (currentNode->hasLeftNode()) {
            currentNode->useSpacing(true);
            currentNode->setSpacingDirection(0);
            currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        }
    }
}

void ICPTree::calculateMaxMinXYAssumingNoSwitch() {
    maxX = -1e8;
    minX = 1e8;
    maxY = -1e8;
    minX = 1e8;
    // maxX
    if (maxX < exteriorRightContour->getMaxY()) {
        maxX = exteriorRightContour->getMaxY();
    }
    if (maxX < exteriorTopContour->getMaxX()) {
        maxX = exteriorTopContour->getMaxX();
    }
    if (maxX < interiorRightContour->getMaxY()) {
        maxX = interiorRightContour->getMaxY();
    }
    // minX
    if (minX > exteriorTopContour->getMinX()) {
        minX = exteriorTopContour->getMinX();
    }
    if (minX > exteriorLeftContour->getMaxY()) {
        minX = exteriorLeftContour->getMaxY();
    }
    if (minX > exteriorBottomContour->getMaxX()) {
        minX = exteriorBottomContour->getMaxX();
    }
    if (minX > interiorLeftContour->getMaxY()) {
        minX = interiorLeftContour->getMaxY();
    }
    // maxY
    if (maxY < exteriorTopContour->getMaxY()) {
        maxY = exteriorTopContour->getMaxY();
    }
    if (maxY < exteriorLeftContour->getMaxX()) {
        maxY = exteriorLeftContour->getMaxX();
    }
    if (maxY < interiorTopContour->getMaxY()) {
        maxY = interiorTopContour->getMaxY();
    }
    // minY
    if (minY > exteriorBottomContour->getMaxY()) {
        minY = exteriorBottomContour->getMaxY();
    }
    if (minY > exteriorRightContour->getMaxX()) {
        minY = exteriorRightContour->getMaxX();
    }
    if (minY > interiorBottomContour->getMaxY()) {
        minY = interiorBottomContour->getMaxY();
    }
}

void ICPTree::calculateBoundingBoxArea() {
    boundingBoxArea = (maxX - minX) * (maxY - minY);
}

void ICPTree::calculateInteriorRegionArea() {
    interiorRegionArea = boundingBoxArea;
    // Corner 0
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *currentNode = root;
    Macro *macro = currentNode->getMacro();
    int extendedMacroArea = (macro->getXEnd() - minX) * (maxY - macro->getYStart());
    extendedMacroArea += currentNode->getSpacing() * (maxY - macro->getYEnd());
    interiorRegionArea -= extendedMacroArea;
    // Top branch
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    macro = currentNode->getMacro();
    while (!currentNode->isCornerNode()) {
        extendedMacroArea = macro->getWidth() * (maxY - macro->getYStart());
        extendedMacroArea += currentNode->getSpacing() * (maxY - macro->getYEnd());
        interiorRegionArea -= extendedMacroArea;
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        macro = currentNode->getMacro();
    }
    // Corner 1
    extendedMacroArea = (maxX - macro->getXStart()) * (maxY - macro->getYStart());
    extendedMacroArea += (maxX - macro->getXEnd()) * currentNode->getSpacing();
    interiorRegionArea -= extendedMacroArea;
    // Right branch
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    macro = currentNode->getMacro();
    while (!currentNode->isCornerNode()) {
        extendedMacroArea = macro->getHeight() * (maxX - macro->getXStart());
        extendedMacroArea += currentNode->getSpacing() * (maxX - macro->getXEnd());
        interiorRegionArea -= extendedMacroArea;
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        macro = currentNode->getMacro();
    }
    // Corner 2
    extendedMacroArea = (macro->getYEnd() - minY) * (maxX - macro->getXStart());
    extendedMacroArea += (macro->getYStart() - minY) * currentNode->getSpacing();
    interiorRegionArea -= extendedMacroArea;
    // Bottom branch
    currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
    macro = currentNode->getMacro();
    while (!currentNode->isCornerNode()) {
        extendedMacroArea = macro->getWidth() * (macro->getYEnd() - minY);
        extendedMacroArea += currentNode->getSpacing() * (macro->getYStart() - minY);
        interiorRegionArea -= extendedMacroArea;
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        macro = currentNode->getMacro();
    }
    // Corner 3
    extendedMacroArea = (macro->getXEnd() - minX) * (macro->getYEnd() - minY);
    extendedMacroArea += (macro->getXStart() - minX) * currentNode->getSpacing();
    interiorRegionArea -= extendedMacroArea;
    // Left branch
    if (currentNode->hasLeftNode()) {
        currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
        macro = currentNode->getMacro();
        int corner0YStart = root->getMacro()->getYStart();
        while (macro->getYStart() < corner0YStart) {
            int macroHeight = macro->getHeight();
            int validMacroHight = macroHeight;
            if (macro->getYEnd() + currentNode->getSpacing() > corner0XStart) {
                validMacroHight = corner0XStart - macro->getYStart();
            }
            int validSpacing = 0;
            if (validMacroHight > macroHeight) {
                validSpacing = validMacroHight - macroHeight;
                validMacroHight = macroHeight;
            }
            extendedMacroArea = validMacroHight * (macro->getXEnd() - minX);
            interiorRegionArea -= extendedMacroArea;
            if (currentNode->hasLeftNode()) {
                currentNode = dynamic_cast<MacroNode *>(currentNode->getLeftNode());
                macro = currentNode->getMacro();    
            } else {
                break;
            }
        }
    }
}