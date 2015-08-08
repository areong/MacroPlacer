#ifndef TREE_ICPTREE_ICPTREE_H_
#define TREE_ICPTREE_ICPTREE_H_

#include "tree/binarytree/BinaryTree.h"
#include <vector>

class MacroNode;
class Contour;

/*
CAUTION: The Nodes used in ICPTree methods are actually MacroNodes.
Please use MacroNode in every input with Node class.
Maybe a refractoring can be done to force using MacroNode.
*/
class ICPTree : public BinaryTree {
public:
    ICPTree();
    ~ICPTree();
    /*
    @Override
    First call BinaryTree.initializeRandomly(), then call
    ICPTree.initializeMacroNodesOnBranchesRandomly().
    */
    void initializeRandomly();
    /*
    Assume the tree structure is ready.
    Set the root as a CornerNode. Traverse all left Nodes and randomly
    select three Nodes and set them as CornerNodes. Set the other Nodes
    on branches as BranchNodes. The rest are NormalNodes by default.
    */
    void initializeMacroNodesOnBranchesRandomly();
    /*
    @Override
    */
    void insertLeftNode(Node *node, Node *position);
    /*
    @Override
    */
    void insertRightNode(Node *node, Node *position);
    /*
    @Override
    */
    void swapNodes(Node *node1, Node *node2);
    int setCorner0Position(int x, int y);
    /*
    Get the ith CornerNode. ith = 0, 1, 2, or 3.
    Get CornerNode by traversing from the root.
    
    @return The CornerNode. Return 0 if ith < 0 or ith > 3.
    */
    MacroNode *getCornerNode(int ith);
    /*
    Get all CornerNodes in a vector.
    PLEASE DELETE the returned vector.
    Get CornerNodes by traversing from the root.
    */
    std::vector<MacroNode *> *getCornerNodes();
    /*
    Get a non-empty BranchNode randomly.

    @return Return 0 if no non-empty BranchNode exists.
    */
    MacroNode *getNonEmptyBranchNodeRandomly();
    /*
    Get a SwitchNode randomly. SwitchNodes are all non-empty.

    @return Return 0 if no SwitchNode exists.
    */
    MacroNode *getSwitchNodeRandomly();
    /*
    Get a MacroNode on branches randomly. Used for inserting empty Nodes.
    The MacroNode's leftNode is not an empty Node.
    
    @return Return 0 if no MacroNode can be inserted an empty Node.
    */
    MacroNode *getEmptyNodeInsertableMacroNodeRandomly();
    /*
    Get a vector of all empty Nodes.
    PLEASE DELETE the returned vector.
    Get empty Nodes by traversing from the root.
    */
    std::vector<MacroNode *> *getEmptyNodes();
    /*
    Get an empty Node randomly.

    @return Return 0 if no empty Node exists.
    */
    MacroNode *getEmptyNodeRandomly();
    /*
    Move the Corner forward or backward by one Node by setting the identity
    of MacroNodes.

    @param ith  Can only be 1, 2 or 3, which indicates one of the four CornerNodes.
                The first CornerNode cannot be moved so not included.
    @return     If the Corner cannot be moved, return false; else return true.
    */
    bool moveCorner(int ith, bool forward);
    bool moveCornerRandomly();
    /*
    Node must be a BranchNode.
    Set the BranchNode as a SwitchNode.
    */
    void assignSwitch(MacroNode *node);
    void assignSwitchRandomly();
    /*
    Node must be a SwitchNode.
    Move the Switch forward or backward by one Node.
    @return     Return false if the Switch cannot be moved; else return true.
    */
    bool moveSwitch(MacroNode *node, bool forward);
    bool moveSwitchRandomly();
    /*
    Node must be a SwitchNode.
    Set the SwitchNode as a BranchNode.
    */
    void removeSwitch(MacroNode *node);
    void removeSwitchRandomly();
    /*
    Insert an empty Node as the left Node of position.
    The inserted Node is an empty BranchNode.

    @param position Must be a non-empty BranchNode, SwichNode or
                    a CornerNode, and its left Node is not an empty Node.
    */
    void insertEmptyNode(MacroNode *position);
    void insertEmptyNodeRandomly();
    /*
    Remove the given empty Node.
    If the node is a CornerNode, try to move the Corner first.
    @param node Must be an empty Node.
    @return     If remove unsuccessfully, return false; else return true.
    */
    bool removeEmptyNode(MacroNode *node);
    bool removeEmptyNodeRandomly();
    /*
    Traverse all MacroNodes in ICPTree manner:
    Collect all CornerNodes and SwitchNodes, add each their leftNode into a list.
    Call traverseDfs() with starting Node picked up from the list in the
    reverse order. Then traverse corner 0 by traverseDfs.
    */
    void traverseAll(TraversalTask *task);
    /*
    A simpler version of placeMacros. It assume there is no Switch exists.
    */
    void placeMacrosAssumingNoSwitch();
    int getMaxX();
    int getMinX();
    int getMaxY();
    int getMinY();
    /*
    @Override
    */
    BinaryTree *createBinaryTree();

private:
    int corner0XStart;
    int corner0YStart;

    Contour *exteriorTopContour;
    Contour *exteriorRightContour;
    Contour *exteriorBottomContour;
    Contour *exteriorLeftContour;
    Contour *interiorBottomContour;
    Contour *interiorLeftContour;
    Contour *interiorTopContour;
    Contour *interiorRightContour;

    int maxX;
    int minX;
    int maxY;
    int minY;

    void swapMacroNodesIdentity(MacroNode *node1, MacroNode *node2);
    void swapMacroNodesPackingDirection(MacroNode *node1, MacroNode *node2);
    /*
    Get the starting MacroNode for ICPTree.traverseAll().
    */
    MacroNode *getLeftMostMacroNode();
    /*
    Return 0 to 3 indicating which CornerNode the node is.
    Return -1 if equals to non of each CornerNode.
    */
    int getWhichCornerNodeIs(MacroNode *node);
    /*
    Update the packing direction of all MacroNodes on branches.
    This method is called at the beginning of traverseAll() and placeMacros()
    
    DISCUSSION: If methods like moveCorner(), moveSwitch(), assignSwitch(), etc. do
    update MacroNode.packingForward, than calling this method is not necessary.
    However this would require more code and make those methods more complicated.
    */
    void updatePackingDirectionOfMacroNodesOnBranches();
    /*
    Delete and create Contours.
    */
    void initializeContours();
    /*
    Call MacroNode.isCovered(false) for all MacroNodes.
    */
    void setAllMacroNodesNotCovered();
    /*
    Called at the end of placing Macros to calculate the x y range of Macros.
    Assume no Switch is used (calculation is a little bit simpler than with Switch).
    */
    void calculateMaxMinXYAssumingNoSwitch();
};

#endif