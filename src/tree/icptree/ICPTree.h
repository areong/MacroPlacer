#ifndef TREE_ICPTREE_ICPTREE_H_
#define TREE_ICPTREE_ICPTREE_H_

#include "tree/binarytree/BinaryTree.h"
#include <vector>

class MacroNode;

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
    Traverse all MacroNodes in ICPTree manner.
    */
    void traverseAll(TraversalTask *task);
    /*
    @Override
    */
    BinaryTree *createBinaryTree();

private:
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
};

#endif