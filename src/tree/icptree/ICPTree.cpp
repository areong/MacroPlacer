#include "tree/icptree/ICPTree.h"
#include "tree/icptree/MacroNode.h"
#include "utils/Utils.h"

#include <iostream>

ICPTree::ICPTree() {

}

ICPTree::~ICPTree() {

}

void ICPTree::initializeRandomly() {
    BinaryTree::initializeRandomly();
    initializeMacroNodesOnBranchesRandomly();
}

void ICPTree::initializeMacroNodesOnBranchesRandomly() {
    // Set the root as a CornerNode.
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    root->setAsCornerNode();
    // Traverse left Nodes, count the number of MacroNodes.
    int numNonEmptyMacroNodesOnBranches = 0;
    MacroNode *current = root;  // Assume root is not 0.
    while (true) {
        numNonEmptyMacroNodesOnBranches += 1;
        if (current->hasLeftNode()) {
            current = dynamic_cast<MacroNode *>(current->getLeftNode());
        } else {
            break;
        }
    }
    // If numNonEmptyMacroNodesOnBranches is less then four,
    // insert empty Node at the leftMostNode (for now it is current)
    // and set the leftNodes of root as CornerNodes.
    if (numNonEmptyMacroNodesOnBranches < 4) {
        for (int i = numNonEmptyMacroNodesOnBranches; i < 4; i++) {
            insertEmptyNode(current);
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
            if (i == iths->at(whichIth)) {
                current->setAsCornerNode();
                if (whichIth >= 2)
                    break;
                whichIth += 1;
            } else {
                current->setAsBranchNode();
            }
            current = dynamic_cast<MacroNode *>(current->getLeftNode());
        }
        delete iths;   
    }
}

void ICPTree::insertLeftNode(Node *node, Node *position) {
    BinaryTree::insertLeftNode(node, position);
    // Set idenitiy.
    MacroNode *mn_node = dynamic_cast<MacroNode *>(node);
    MacroNode *mn_position = dynamic_cast<MacroNode *>(position);
    if (mn_node != 0 && mn_position != 0) {     // BinaryTree uses this method with Node.
        switch (mn_position->getIdentity()) {
            case MacroNode::NORMAL_NODE:
                mn_node->setAsNormalNode();
                break;
            case MacroNode::BRANCH_NODE:
                mn_node->setAsBranchNode();
                break;
            case MacroNode::SWITCH_NODE:
                mn_node->setAsBranchNode();
                break;
            case MacroNode::CORNER_NODE:
                mn_node->setAsBranchNode();
                break;
            default:
                mn_node->setAsNormalNode();
                break;
        }
    }
}

void ICPTree::insertRightNode(Node *node, Node *position) {
    BinaryTree::insertRightNode(node, position);
    // Set as a Normal Node.
    MacroNode *mn_node = dynamic_cast<MacroNode *>(node);
    if (mn_node != 0)   // BinaryTree uses this method with Node.
        mn_node->setAsNormalNode();
}

void ICPTree::swapNodes(Node *node1, Node *node2) {
    BinaryTree::swapNodes(node1, node2);
    // Exchange identity.
    MacroNode *mn_node1 = dynamic_cast<MacroNode *>(node1);
    MacroNode *mn_node2 = dynamic_cast<MacroNode *>(node2);
    if (mn_node1 != 0 && mn_node2 != 0) {   // BinaryTree uses this method with Node.
        swapMacroNodesIdentity(mn_node1, mn_node2);
        int verticalDisplacement1 = mn_node1->getVerticalDisplacement();
        mn_node1->setVerticalDisplacement(mn_node2->getVerticalDisplacement());
        mn_node2->setVerticalDisplacement(verticalDisplacement1);
    }
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

MacroNode *ICPTree::getEmptyNodeRandomly() {
    std::vector<MacroNode *> *emptyNodes = new std::vector<MacroNode *>();
    MacroNode *root = dynamic_cast<MacroNode *>(getRoot());
    MacroNode *current = root;
    while (current != 0) {
        if (current->isEmptyNode())
            emptyNodes->push_back(current);
        current = dynamic_cast<MacroNode *>(current->getLeftNode());
    }
    MacroNode *result = 0;
    if (emptyNodes->size() > 0)
        result = emptyNodes->at(Utils::randint(0, emptyNodes->size()));
    delete emptyNodes;
    return result;
}

bool ICPTree::moveCorner(int ith, bool forward) {
    // Forward
    // C-C: do nothing.
    // B-C: set B Corner, set C Branch.
    // S-C: set S Corner, set C Branch.
    // Backward
    // C-C: do nothing.
    // C-B: set B Corner, set C Branch.
    // C-S: set S Corner, set C Branch.
    MacroNode *corner = getCornerNode(ith);
    MacroNode *target;
    if (forward)
        target = dynamic_cast<MacroNode *>(corner->getParentNode());   // Always exists.
    else
        target = dynamic_cast<MacroNode *>(corner->getLeftNode());     // Might not exists.
    if (target == 0)
        return false;
    else if (target->isCornerNode())
        return false;
    corner->setAsBranchNode();
    target->setAsCornerNode();
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
        // Do not need removeNode() because an empty Node does not have
        // right Node.
        Node *parent = node->getParentNode();
        Node *leftNode = node->getLeftNode();
        parent->setLeftNode(leftNode);
        if (leftNode != 0)
            leftNode->setParentNode(parent);
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

void ICPTree::traverseAll(TraversalTask *task) {
    // The packing direction migh have changed.
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
}

BinaryTree *ICPTree::createBinaryTree() {
    return new ICPTree();
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