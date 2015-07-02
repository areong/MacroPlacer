#ifndef TREE_ICPTREE_MACRONODE_H_
#define TREE_ICPTREE_MACRONODE_H_

#include "tree/binarytree/Node.h"

class MacroNode : public Node {
public:
    MacroNode();
    ~MacroNode();
    enum Identity {
        NORMAL_NODE,
        BRANCH_NODE,
        SWITCH_NODE,
        CORNER_NODE
    };
    void setIdentity(MacroNode::Identity identity);
    MacroNode::Identity getIdentity();
    void setAsNormalNode();
    void setAsBranchNode();
    void setAsSwitchNode();
    void setAsCornerNode();
    bool isNormalNode();
    bool isBranchNode();
    bool isSwitchNode();
    bool isCornerNode();
    void setPackingDirection(bool forward);
    void changePackingDirection();
    bool isPackingForward();
    /*
    Set the MacroNode be empty.
    */
    void setEmpty();
    bool isEmptyNode();
    /*
    Create a MacroNode, set it empty and return it.
    */
    static MacroNode *createEmptyNode();
    /*
    Create a MacroNode by copying some info from node, set it empty and return it.
    Copied info: width, height and verticalDisplacement.
    */
    static MacroNode *createEmptyNode(MacroNode *node);

private:
    bool packingForward;
    MacroNode::Identity identity;
    bool empty;

    void updateBranchNodeNextNodesBehavior();
};

#endif