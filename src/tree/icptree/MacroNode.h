#ifndef TREE_ICPTREE_MACRONODE_H_
#define TREE_ICPTREE_MACRONODE_H_

#include "tree/binarytree/Node.h"

class Edge;
class Macro;

class MacroNode : public Node {
public:
    MacroNode();
    MacroNode(Macro *macro);
    /*
    If it is an empty Node, delete its Macro; else do not delete.
    */
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
    void setMacro(Macro *macro);
    Macro *getMacro();
    void setVerticalDisplacement(int displacement);
    /*
    Add the displacement to the current verticalDisplacement.
    */
    void addToVerticalDisplacement(int displacement);
    int getVerticalDisplacement();
    void setCovered(bool covered);
    bool isCovered();
    /*
    @Override
    */
    Node *createNode();
    /*
    @Override
    If it is an empty Node, copy its Macro; else set to the old Macro.
    */
    Node *copy();
    /*
    Used in MacroNode::copy(). Using the original setters invokes
    other setters like setAsBranchNode, which might create new object
    and cause memory leaks. This method simply copy the attributes.
    */
    void setAttributes(bool packingForward, MacroNode::Identity identity, bool empty);
    /*
    Create a MacroNode, set it empty and return it.
    */
    static MacroNode *createEmptyNode();
    /*
    Create a MacroNode by copying some info from node, set it empty and return it.
    Copied info: width, height and verticalDisplacement.
    */
    static MacroNode *createEmptyNode(MacroNode *node);

    // Edges

    Edge *createTopEdge();
    Edge *getTopEdge();
    Edge *createRightEdge();
    Edge *getRightEdge();
    Edge *createBottomEdge();
    Edge *getBottomEdge();
    Edge *createLeftEdge();
    Edge *getLeftEdge();

private:
    bool packingForward;
    MacroNode::Identity identity;
    bool empty;

    Macro *macro;
    int verticalDisplacement;

    void updateBranchNodeNextNodesBehavior();

    // The following will not be copied when calling MacroNode.copy().

    /*
    It is true if another Macro is placed on top of its Macro such that
    its Edge is removed from the Contour.
    */
    bool covered;

    Edge *topEdge;
    Edge *rightEdge;
    Edge *bottomEdge;
    Edge *leftEdge;
};

#endif