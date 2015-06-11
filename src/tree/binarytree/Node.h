#ifndef TREE_BINARYTREE_NODE_H_
#define TREE_BINARYTREE_NODE_H_

#include <vector>

class NextNodesBehavior;

class Node {
public:
    Node();
    ~Node();
    /*
    THE METHOD IS DESIGNED ONLY TO BE USED BY BINARYTREE.
    BinaryTree assign id to its Nodes to make copying and deleting BinaryTree
    more easier.
    */
    void _setId(int id);
    /*
    THE METHOD IS DESIGNED ONLY TO BE USED BY BINARYTREE.
    */
    int _getId();
    void setParentNode(Node *node);
    Node *getParentNode();
    void setLeftNode(Node *node);
    Node *getLeftNode();
    void setRightNode(Node *node);
    Node *getRightNode();
    bool isLeftNode();
    bool hasLeftNode();
    bool hasRightNode();
    /*
    Create a copy of the Node. This method is called when calling BinaryTree.copy().
    For a subclass of Node, call Node::copy() inside copy().
    If implement this method by a copy constructor, the copy constructor of a Node's subclass
    will (?) not be called when copying a Node.
    */
    virtual Node *copy();
    /*
    Change the behavior of Node.getNextNodes().
    The behavior will be deleted when the Node is deleted or a new behavior is set,
    so please CREATE A NEW NextNodesBehavior for each Node.
    */
    void setNextNodesBehavior(NextNodesBehavior *behavior);
    /*
    Used in BinaryTree.traverseDfs().
    The behavior of this method can be set by calling Node.setN
    */
    std::vector<Node *> *getNextNodes();

private:
    Node *parentNode;
    Node *leftNode;
    Node *rightNode;
    int id;
    NextNodesBehavior *nextNodesBehavior;
};

#endif