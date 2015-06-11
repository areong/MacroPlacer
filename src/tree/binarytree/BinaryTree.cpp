#include "tree/binarytree/BinaryTree.h"
#include "tree/binarytree/Node.h"
#include "tree/binarytree/TraversalTask.h"

BinaryTree::BinaryTree() {
    nodes = new std::vector<Node *>();
    head = new Node();
    addNode(head);
}

BinaryTree::~BinaryTree() {
    for (int i = 0; i < nodes->size(); i++)
        delete nodes->at(i);
    delete nodes;
}

void BinaryTree::addNode(Node *node) {
    node->_setId(nodes->size());
    nodes->push_back(node);
}

Node *BinaryTree::_getNodeById(int id) {
    return nodes->at(id);
}

void BinaryTree::setRoot(Node *node) {
    if (head->hasLeftNode()) {
        Node *headLeft = head->getLeftNode();
        swapNodes(node, headLeft);
    } else {
        head->setLeftNode(node);
        node->setParentNode(head);
    }
}

Node *BinaryTree::getRoot() {
    return head->getLeftNode();
}

void BinaryTree::insertLeftNode(Node *node, Node *position) {
    Node *oldLeft = position->getLeftNode();
    node->setParentNode(position);
    node->setLeftNode(oldLeft);
    position->setLeftNode(node);
    if (oldLeft != 0)
        oldLeft->setParentNode(node);
}

void BinaryTree::insertRightNode(Node *node, Node *position) {
    Node *oldRight = position->getRightNode();
    node->setParentNode(position);
    node->setRightNode(oldRight);
    position->setRightNode(node);
    if (oldRight != 0)
        oldRight->setParentNode(node);
}

void BinaryTree::removeNode(Node *node, bool replaceWithLeftNode) {
    if (replaceWithLeftNode) {
        while (true) {
            if (node->hasLeftNode())
                swapNodes(node, node->getLeftNode());
            else if (node->hasRightNode())
                swapNodes(node, node->getRightNode());
            else
                break;
        }
    } else {
        while (true) {
            if (node->hasRightNode())
                swapNodes(node, node->getRightNode());
            else if (node->hasLeftNode())
                swapNodes(node, node->getLeftNode());
            else
                break;
        }
    }
    if (node->isLeftNode())
        node->getParentNode()->setLeftNode(0);
    else
        node->getParentNode()->setRightNode(0);
    node->setParentNode(0);
}

void BinaryTree::swapNodes(Node *node1, Node *node2) {
    // 1. If the two Nodes are connected together, insert a dummy Node.
    Node *dummy = new Node();
    int situation = 0;
    if (node1->getLeftNode() == node2) {
        insertLeftNode(dummy, node1);
        situation = 1;
    } else if (node1->getRightNode() == node2) {
        insertRightNode(dummy, node1);
        situation = 2;
    } else if (node2->getLeftNode() == node1) {
        insertLeftNode(dummy, node2);
        situation = 3;
    } else if (node2->getRightNode() == node1) {
        insertRightNode(dummy, node2);
        situation = 4;
    }
    // 2. Exchange relations.
    Node *oldNode1Parent = node1->getParentNode();
    Node *oldNode1Left = node1->getLeftNode();
    Node *oldNode1Right = node1->getRightNode();
    Node *oldNode2Parent = node2->getParentNode();
    Node *oldNode2Left = node2->getLeftNode();
    Node *oldNode2Right = node2->getRightNode();
    if (oldNode1Parent != 0)    // Node not yet being inserted has no parent.
        if (node1->isLeftNode())
            oldNode1Parent->setLeftNode(node2);
        else
            oldNode1Parent->setRightNode(node2);
    if (oldNode2Parent != 0)
        if (node2->isLeftNode())
            oldNode2Parent->setLeftNode(node1);
        else
            oldNode2Parent->setRightNode(node1);
    node1->setParentNode(oldNode2Parent);
    node1->setLeftNode(oldNode2Left);
    node1->setRightNode(oldNode2Right);
    node2->setParentNode(oldNode1Parent);
    node2->setLeftNode(oldNode1Left);
    node2->setRightNode(oldNode1Right);
    if (oldNode1Left != 0)
        oldNode1Left->setParentNode(node2);
    if (oldNode1Right != 0)
        oldNode1Right->setParentNode(node2);
    if (oldNode2Left != 0)
        oldNode2Left->setParentNode(node1);
    if (oldNode2Right != 0)
        oldNode2Right->setParentNode(node1);
    // 3. Remove the dummy Node.
    switch (situation) {
        case 1:
            node2->setLeftNode(node1);
            node1->setParentNode(node2);
            break;
        case 2:
            node2->setRightNode(node1);
            node1->setParentNode(node2);
            break;
        case 3:
            node1->setLeftNode(node2);
            node2->setParentNode(node1);
            break;
        case 4:
            node1->setRightNode(node2);
            node2->setParentNode(node1);
            break;
        default:
            break;
    }
    delete dummy;
}

void BinaryTree::traverseDfs(Node *start, TraversalTask *task) {
    std::vector<Node *> *discovered = new std::vector<Node *>();
    discovered->push_back(start);
    Node *current;
    while (discovered->size() > 0) {
        // Get the last discovered Node.
        current = discovered->back();
        discovered->pop_back();
        // Perform task.
        task->doWhenTraversing(current);
        // Get its next Nodes.
        std::vector<Node *> *nextNodes = current->getNextNodes();
        // Add to discovered from back to front such that the front
        // will be the next current.
        for (int i = nextNodes->size() - 1; i >= 0; i--)
            discovered->push_back(nextNodes->at(i));
        // Delete the vector because it is created in Node.getNextNodes().
        delete nextNodes;
    }
    delete discovered;
}

BinaryTree *BinaryTree::copy() {
    BinaryTree *binaryTree = new BinaryTree();
    // The first Node is the head, which is already created and do not need to be copied.
    for (int i = 1; i < nodes->size(); i++)
        // If the Node is actually a Node's subclass, then the subclass's copy() will be called.
        binaryTree->addNode(nodes->at(i)->copy());
    // Connect the Nodes.
    for (int i = 0; i < nodes->size(); i++) {
        Node *oldNode = nodes->at(i);
        Node *newNode = binaryTree->_getNodeById(i);    // i equals id
        // Do not use insert methods because it changes one of the child Node
        // of the inserted Node.
        if (oldNode->hasLeftNode()) {
            Node *newLeftNode = binaryTree->_getNodeById(oldNode->getLeftNode()->_getId());
            newNode->setLeftNode(newLeftNode);
            newLeftNode->setParentNode(newNode);
        }
        if (oldNode->hasRightNode()) {
            Node *newRightNode = binaryTree->_getNodeById(oldNode->getRightNode()->_getId());
            newNode->setRightNode(newRightNode);
            newRightNode->setParentNode(newNode);
        }
    }
    return binaryTree;
}