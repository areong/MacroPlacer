#ifndef TREE_BINARYTREE_BINARYTREE_H_
#define TREE_BINARYTREE_BINARYTREE_H_

#include <vector>

class Node;
class TraversalTask;

class BinaryTree {
public:
    BinaryTree();
    /*
    Delete all Nodes in the tree.
    */
    ~BinaryTree();
    /*
    Please add all Nodes before operating on them, including setRoot, insert, remove and swap.
    Do not add a Node more than once.
    */
    void addNode(Node *node);
    /*
    THE METHOD IS DESIGNED ONLY TO BE USED BY BINARYTREE.
    When adding Node to BinaryTree, the Node's id is assigned.
    This method get a Node by its id without checking whether the id is valid.
    */
    Node *_getNodeById(int id);
    void setRoot(Node *node);
    Node *getRoot();
    /*
    Insert node between position and position.getLeftNode().
    */
    void insertLeftNode(Node *node, Node *position);
    /*
    Insert node between position and position.getRightNode().
    */
    void insertRightNode(Node *node, Node *position);
    /*
    Remove a Node by swapping with its leftNode or rightNode recursively
    until no child exists, and then detaching the Node.
    @param  replaceWithRightNode    If true, swap with leftNode, or swap with
                                    rightNode unless there is no leftNode.
    */
    void removeNode(Node *node, bool replaceWithLeftNode);
    void swapNodes(Node *node1, Node *node2);
    /*
    Traverse the Nodes in dfs order. How the Nodes return their next Nodes
    and what to do when traversing each Node are determined by the NodeBehavior
    of each Node.
    */
    void traverseDfs(Node *start, TraversalTask *task);
    /*
    Copy the tree and the Nodes added to the tree.
    For a subclass of BinaryTree, call BinaryTree::copy() inside copy().
    If an object of a BinaryTree's subclass is composed of objects of Node's subclass, the Node's
    subclass's copy will be called.
    */
    virtual BinaryTree *copy();

private:
    std::vector<Node *> *nodes;
    Node *head;
};

#endif