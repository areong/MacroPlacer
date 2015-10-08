#ifndef TREE_ICPTREE_ICPTREE_H_
#define TREE_ICPTREE_ICPTREE_H_

#include "tree/binarytree/BinaryTree.h"
#include <vector>

class Macro;
class MacroNode;
class Contour;

/*
CAUTION: The Nodes used in ICPTree methods are actually MacroNodes.
Please use MacroNode in every input with Node class.
Maybe a refractoring can be done to force using MacroNode.
*/
class ICPTree : public BinaryTree {
public:
    /*
    @param macros If not zero, create MacroNodes from the macros and
                  add the MacroNodes to the ICPTree by ICPTree.addNode().
    */
    ICPTree(std::vector<Macro *> *macros=0);
    ~ICPTree();
    /*
    @Override
    First call BinaryTree.initializeRandomly(), then call
    ICPTree.initializeMacroNodesOnBranchesRandomly() and
    ICPTree.updateMacroNodesOnBranchesBranchNumber().
    */
    void initializeRandomly();
    /*
    Assume the tree structure is ready.
    Set the root as a CornerNode. Traverse all left Nodes and randomly
    select three Nodes and set them as CornerNodes. Set the other Nodes
    on branches as BranchNodes. The rest are NormalNodes by default.
    If there are less than four MacroNodes on branches, remove some
    NormalNodes and insert at the left-most MacroNode as leftNodes.
    ASSUME there are at least four MacroNodes added to the ICPTree.
    */
    void initializeMacroNodesOnBranchesRandomly();
    /*
    Initialize as a balanced ICPTree, in which the Macros distribute evenly
    around the rectangular interior region and within the desired region if possible.
    ASSUME the area of the desired region is not less then the target
    interior region area.
    ASSUME there are at least four MacroNodes added.
    @param xStart The four integers are the range of the desired region.
    @param targetInteriorRegionArea The area left at center.
    */
    void initializeBalancedICPTreeRandomly(int xStart, int yStart, int xEnd, int yEnd, int targetInteriorRegionArea);
    /*
    @Override
    */
    void insertLeftNode(Node *node, Node *position);
    /*
    @Override
    */
    void insertRightNode(Node *node, Node *position);
    /*
    Insert as leftNode or rightNode according to the MacroNode's Macro's aspect ratio
    and which subtree the macroNode is inserted into.
    For example, if a MacroNode whose Macro's aspect ratio is 2, and the MacroNode
    is inserted to topSubtree, then the probability of inserting as leftNode is 2/3.
    */
    void insertMacroNodeByMacroAspectRatio(MacroNode *macroNode, MacroNode *position, int subtreeNumber);
    /*
    @Override
    Check if the MacroNode can be removed or not.
    */
    bool removeNode(Node *node, bool replaceWithLeftNode);
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
    Get a non-empty MacroNode on branches randomly.
    Used by changing verticalDisplacement.
    Corner 0 is excluded.
    */
    MacroNode *getNonEmptyMacroNodeOnBranchesRandomly();
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
    /*
    The same as moveCorner(int, bool) except for the input is a CornerNode.
    @param cornerNode must be a CornerNode.
    */
    bool moveCorner(MacroNode *cornerNode, bool forward);
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
    When calling ICPTree.changeRandomEmptyNodeWidthRandomly(), the chosen
    MacroNode's Macro's width will change by ±changeRange.
    */
    void setChangeRangeOfEmptyNodeWidth(int changeRange);
    /*
    When calling ICPTree.changeRandomMacroNodeVerticalDisplacementRandomly(),
    the chosen MacroNode's verticalDisplacement will change by ±changeRange.
    */
    void setChangeRangeOfVerticalDisplacement(int changeRange);
    /*
    MacroNode.spacing will change by ±changeRange and keep non-negative.
    */
    void setChangeRangeOfSpacing(int changeRange);
    /*
    When calling ICPTree.changeCorner0PositionRandomly(),
    corner 0's x and y will change by ±changeRange.
    */
    void setChangeRangeOfCorner0Position(int changeRange);
    void changeRandomEmptyNodeWidthRandomly();
    /*
    Choose a non-empty MacroNode on branches (exluding corner 0)
    and set its verticalDisplacement.
    If its leftNode is an empty Node, also set the leftNode's
    verticalDisplacement to the same value; if the chosen MacroNode
    is a CornerNode, set to zero.
    */
    void changeRandomMacroNodeVerticalDisplacementRandomly();
    void changeRandomMacroNodeSpacingRandomly();
    void changeCorner0PositionRandomly();
    void rotateRandomMacroRandomly();
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
    Please call ICPTree.placeMacrosAssumingNoSwitch() beforehand.
    */
    int getBoundingBoxArea();
    /*
    Please call ICPTree.placeMacrosAssumingNoSwitch() beforehand.
    */
    int getInteriorRegionArea();
    /*
    Please call ICPTree.placeMacrosAssumingNoSwitch() beforehand.
    */
    double getBoundingBoxAspectRatio();
    /*
    @Override
    */
    BinaryTree *createBinaryTree();
    /*
    @Override
    */
    BinaryTree *copy();

private:
    int desiredRegionXStart;
    int desiredRegionYStart;
    int desiredRegionXEnd;
    int desiredRegionYEnd;

    int corner0XStart;
    int corner0YStart;

    int changeRangeOfEmptyNodeWidth;
    int changeRangeOfVerticalDisplacement;
    int changeRangeOfSpacing;
    int changeRangeOfCorner0Position;

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
    int boundingBoxArea;
    int interiorRegionArea;

    /*
    Choose a MacroNode from availableNodes, erase it, push it into selectedNodes
    and then return it.
    */
    MacroNode *selectMacroNodeRandomly(std::vector<MacroNode *> *availableNodes,
        std::vector<MacroNode *> *selectedNodes);

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
    void createContours();
    /*
    Update the branchNumber of the MacroNodes on branches.
    It is called in ICPTree.placeMacros...() before placing Macros.
    */
    void updateMacroNodesOnBranchesBranchNumber();
    /*
    Merge empty BranchNodes to one empty BranchNode if they connect with
    each other on a branch.
    Call it after ICPTree.updateMacroNodesOnBranchesBranchNumber().
    */
    void mergeContiguousEmptyBranchNodes();
    /*
    Call MacroNode.isCovered(false) for all MacroNodes.
    */
    void setAllMacroNodesNotCovered();
    /*
    Call MacroNode.useSpacing(false) for all MacroNodes.
    */
    void setAllMacroNodesNotUsingSpacing();
    /*
    For all MacroNodes on branches, set their spacingDirection by the branches.
    Also set them to use spacing.
    For Corner 1, 2, 3 and the left-most MacroNode, do not set.
    PLEASE call setAllMacroNodesNotUsingSpacing() before for the best result.
    ASSUME there is no SwitchNode.
    */
    void setMacroNodesOnBranchesSpacingDirection();
    /*
    Called at the end of placing Macros to calculate the x y range of Macros.
    Assume no Switch is used (calculation is a little bit simpler than with Switch).
    */
    void calculateMaxMinXYAssumingNoSwitch();
    void calculateBoundingBoxArea();
    /*
    Assume ICPTree.calculateBoundingBoxArea() is called beforehand.
    */
    void calculateInteriorRegionArea();
};

#endif