#include "tree/icptree/MacroNode.h"
#include "tree/binarytree/NextNodesBehaviorLeftFirst.h"
#include "tree/binarytree/NextNodesBehaviorRightFirst.h"
#include "tree/binarytree/NextNodesBehaviorRightOnly.h"

MacroNode::MacroNode() {
    setAsNormalNode();
    setPackingDirection(true);
    empty = false;
}

MacroNode::~MacroNode() {

}

void MacroNode::setIdentity(MacroNode::Identity identity) {
    switch (identity) {
        case MacroNode::NORMAL_NODE:
            setAsNormalNode();
            break;
        case MacroNode::BRANCH_NODE:
            setAsBranchNode();
            break;
        case MacroNode::SWITCH_NODE:
            setAsSwitchNode();
            break;
        case MacroNode::CORNER_NODE:
            setAsCornerNode();
            break;
        default:
            setAsNormalNode();
            break;
    }
}

MacroNode::Identity MacroNode::getIdentity() {
    return identity;
}

void MacroNode::setAsNormalNode() {
    if (identity != MacroNode::NORMAL_NODE) {
        setNextNodesBehavior(new NextNodesBehaviorLeftFirst());
        identity = MacroNode::NORMAL_NODE;
    }
}

void MacroNode::setAsBranchNode() {
    if (identity != MacroNode::BRANCH_NODE) {
        updateBranchNodeNextNodesBehavior();
        identity = MacroNode::BRANCH_NODE;
    }
}

void MacroNode::setAsSwitchNode() {
    if (identity != MacroNode::SWITCH_NODE) {
        setNextNodesBehavior(new NextNodesBehaviorRightOnly());
        identity = MacroNode::SWITCH_NODE;
    }
}

void MacroNode::setAsCornerNode() {
    if (identity != MacroNode::CORNER_NODE) {
        setNextNodesBehavior(new NextNodesBehaviorRightOnly());
        identity = MacroNode::CORNER_NODE;
    }
}

bool MacroNode::isNormalNode() {
    return identity == MacroNode::NORMAL_NODE;
}

bool MacroNode::isBranchNode() {
    return identity == MacroNode::BRANCH_NODE;
}

bool MacroNode::isSwitchNode() {
    return identity == MacroNode::SWITCH_NODE;
}

bool MacroNode::isCornerNode() {
    return identity == MacroNode::CORNER_NODE;
}

void MacroNode::setPackingDirection(bool forward) {
    if (packingForward != forward) {
        packingForward = forward;
        if (identity == MacroNode::BRANCH_NODE)
            updateBranchNodeNextNodesBehavior();
    }
}

void MacroNode::changePackingDirection() {
    packingForward ^= true;
    if (identity == MacroNode::BRANCH_NODE)
        updateBranchNodeNextNodesBehavior();
}

bool MacroNode::isPackingForward() {
    return packingForward;
}

void MacroNode::setEmpty() {
    empty = true;
}

bool MacroNode::isEmptyNode() {
    return empty;
}

MacroNode *MacroNode::createEmptyNode() {
    MacroNode *node = new MacroNode();
    node->setEmpty();
    return node;
}

MacroNode *MacroNode::createEmptyNode(MacroNode *node) {
    // It will copy the width, height and verticalDisplacement of node's Macro.
    // For now since the Macro is not ready, do the same as createEmptyNode().
    MacroNode *emptyNode = new MacroNode();
    emptyNode->setEmpty();
    return emptyNode;
}

void MacroNode::updateBranchNodeNextNodesBehavior() {
    if (packingForward)
        setNextNodesBehavior(new NextNodesBehaviorLeftFirst());
    else
        setNextNodesBehavior(new NextNodesBehaviorRightFirst());
}
