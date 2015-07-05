#include "tree/binarytree/BinaryTree.h"
#include <cstdlib>
#include <ctime>
#include "tree/binarytree/Node.h"
#include "tree/binarytree/TraversalTask.h"
#include "tree/binarytree/TraversalTaskCollectAllNodes.h"
#include "tree/binarytree/TraversalTaskCollectNonAddedNodes.h"

BinaryTree::BinaryTree() {
    srand(time(0));
    nodes = new std::vector<Node *>();
    head = new Node();
}

BinaryTree::~BinaryTree() {
    // If there exists any Node,
    // collect all Nodes by traversing from the root and delete them.
    if (nodes->size() > 0) {
        TraversalTaskCollectAllNodes *task = new TraversalTaskCollectAllNodes();
        traverseDfs(getRoot(), task);
        std::vector<Node *> *allNodes = task->getNodes();
        for (int i = 0; i < allNodes->size(); i++) {
            delete allNodes->at(i);
        }
        delete task;
    }
    delete nodes;
}

void BinaryTree::addNode(Node *node) {
    if (node->getId() < 0)
        node->setId(nodes->size());
    if (node->getId() >= nodes->size())
        nodes->resize(node->getId() + 1, 0);
    nodes->at(node->getId()) = node;
}

Node *BinaryTree::getNodeById(int id) {
    return nodes->at(id);
}

Node *BinaryTree::getNodeRandomly() {
    Node *node = nodes->at(randint(nodes->size()));
    while (node == 0) {
        // If the Nodes' id is not continuous, node might be null.
        node = nodes->at(randint(nodes->size()));
    }
    return node;
}

void BinaryTree::initializeRandomly() {
    // Copy nodes.
    std::vector<Node *> *availableNodes = new std::vector<Node *>(nodes->begin(), nodes->end());
    std::vector<Node *> *insertedNodes = new std::vector<Node *>();
    // Set root.
    int i = randint(availableNodes->size());
    Node *node = availableNodes->at(i);
    while (node == 0) {
        availableNodes->erase(availableNodes->begin() + i);
        i = randint(availableNodes->size());
        node = availableNodes->at(i);
    }
    setRoot(node);
    availableNodes->erase(availableNodes->begin() + i);
    insertedNodes->push_back(node);
    // Connect the rest.
    Node *position;
    while (availableNodes->size() > 0) {
        i = randint(availableNodes->size());
        node = availableNodes->at(i);
        position = insertedNodes->at(randint(insertedNodes->size()));  // Never a null
        while (node == 0) {
            availableNodes->erase(availableNodes->begin() + i);
            i = randint(availableNodes->size());
            node = availableNodes->at(i);
        }
        // Insert as left or right Node.
        if (randbool())
            insertLeftNode(node, position);
        else
            insertRightNode(node, position);
        availableNodes->erase(availableNodes->begin() + i);
        insertedNodes->push_back(node);
    }
    delete availableNodes;
    delete insertedNodes;
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

void BinaryTree::setRoot(int nodeId) {
    setRoot(getNodeById(nodeId));
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

void BinaryTree::insertLeftNode(int nodeId, int positionId) {
    insertLeftNode(getNodeById(nodeId), getNodeById(positionId));
}

void BinaryTree::insertRightNode(Node *node, Node *position) {
    Node *oldRight = position->getRightNode();
    node->setParentNode(position);
    node->setRightNode(oldRight);
    position->setRightNode(node);
    if (oldRight != 0)
        oldRight->setParentNode(node);
}

void BinaryTree::insertRightNode(int nodeId, int positionId) {
    insertRightNode(getNodeById(nodeId), getNodeById(positionId));
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

void BinaryTree::removeNode(int nodeId, bool replaceWithLeftNode) {
    removeNode(getNodeById(nodeId), replaceWithLeftNode);
}

void BinaryTree::removeAndInsertLeftNodeRandomly() {
    Node *node = getNodeRandomly();
    Node *position = getNodeRandomly();
    while (position == node) {
        position = getNodeRandomly();
    }
    removeNode(node, randbool());
    insertLeftNode(node, position);
}

void BinaryTree::removeAndInsertRightNodeRandomly() {
    Node *node = getNodeRandomly();
    Node *position = getNodeRandomly();
    while (position == node) {
        position = getNodeRandomly();
    }
    removeNode(node, randbool());
    insertRightNode(node, position);
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

void BinaryTree::swapNodes(int node1Id, int node2Id) {
    swapNodes(getNodeById(node1Id), getNodeById(node2Id));
}

void BinaryTree::swapNodesRandomly() {
    Node *node1 = getNodeRandomly();
    Node *node2 = getNodeRandomly();
    while (node2 == node1) {
        node2 = getNodeRandomly();
    }
    swapNodes(node1, node2);
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

void BinaryTree::traverseDfs(int startId, TraversalTask *task) {
    traverseDfs(getNodeById(startId), task);
}

BinaryTree *BinaryTree::createBinaryTree() {
    return new BinaryTree();
}

BinaryTree *BinaryTree::copy() {
    BinaryTree *binaryTree = createBinaryTree();
    // If there are no Nodes, return.
    if (nodes->size() == 0)
        return binaryTree;
    // Copy all Nodes.
    for (int i = 0; i < nodes->size(); i++)
        // If the Node is actually a Node's subclass, then the subclass's copy() will be called.
        binaryTree->addNode(nodes->at(i)->copy());
    // Set root.
    Node *newRoot = binaryTree->getNodeById(getRoot()->getId());
    binaryTree->setRoot(newRoot);
    // Connect the Nodes.
    for (int i = 0; i < nodes->size(); i++) {
        Node *oldNode = nodes->at(i);
        Node *newNode = binaryTree->getNodeById(i);    // i equals id
        // Do not use insert methods because it changes one of the child Node
        // of the inserted Node.
        if (oldNode->hasLeftNode()) {
            int id = oldNode->getLeftNode()->getId();
            if (id >= 0) {  // Some Nodes may have not been added by BinaryTree.addNode().
                Node *newLeftNode = binaryTree->getNodeById(id);
                newNode->setLeftNode(newLeftNode);
                newLeftNode->setParentNode(newNode);
            }
        }
        if (oldNode->hasRightNode()) {
            int id = oldNode->getRightNode()->getId();
            if (id >= 0) {
                Node *newRightNode = binaryTree->getNodeById(id);
                newNode->setRightNode(newRightNode);
                newRightNode->setParentNode(newNode);
            }
        }
    }
    // Collect all non-added Nodes (Node.id < 0)
    // by traversing from the root.
    // It is possible that some Nodes in the tree is not added by BinaryTree.addNode()
    // so this step is necessary.
    // ASSUME the root is added by BinaryTree.addNode(),
    // or the following "Connect" part will fail, since the parentNode of the root
    // cannot be get by BinaryTree.getNodeById().
    TraversalTaskCollectNonAddedNodes *task = new TraversalTaskCollectNonAddedNodes();
    traverseDfs(getRoot(), task);
    std::vector<Node *> *oldNonAddedNodes = task->getNodes();
    // Copy
    std::vector<Node *> *newNonAddedNodes = new std::vector<Node *>();
    for (int i = 0; i < oldNonAddedNodes->size(); i++) {
        newNonAddedNodes->push_back(oldNonAddedNodes->at(i)->copy());
    }
    // Connect
    for (int i = 0; i < oldNonAddedNodes->size(); i++) {
        Node *oldNode = oldNonAddedNodes->at(i);
        Node *newNode = newNonAddedNodes->at(i);
        // Parent Node
        Node *oldParentNode = oldNode->getParentNode(); // Always exists.
        Node *newParentNode;
        if (oldParentNode->getId() >= 0) {   // Is added
            newParentNode = binaryTree->getNodeById(oldParentNode->getId());
        } else {    // Not added
            newParentNode = newNonAddedNodes->at(getIndexOf(oldNonAddedNodes, oldParentNode));
        }
        newNode->setParentNode(newParentNode);
        if (oldNode->isLeftNode()) {
            newParentNode->setLeftNode(newNode);
        } else {
            newParentNode->setRightNode(newNode);
        }
        // Left Node
        Node *oldLeftNode = oldNode->getLeftNode();
        if (oldLeftNode != 0) {
            Node *newLeftNode;
            if (oldLeftNode->getId() >= 0) {
                newLeftNode = binaryTree->getNodeById(oldLeftNode->getId());
            } else {
                newLeftNode = newNonAddedNodes->at(getIndexOf(oldNonAddedNodes, oldLeftNode));
            }
            newNode->setLeftNode(newLeftNode);
            newLeftNode->setParentNode(newNode);
        }
        // Right Node
        Node *oldRightNode = oldNode->getRightNode();
        if (oldRightNode != 0) {
            Node *newRightNode;
            if (oldRightNode->getId() >= 0) {
                newRightNode = binaryTree->getNodeById(oldRightNode->getId());
            } else {
                newRightNode = newNonAddedNodes->at(getIndexOf(oldNonAddedNodes, oldRightNode));
            }
            newNode->setRightNode(newRightNode);
            newRightNode->setParentNode(newNode);
        }
    }
    delete newNonAddedNodes;
    delete task;
    return binaryTree;
}

std::vector<Node *> *BinaryTree::getNodes() {
    return nodes;
}

int BinaryTree::randint(int range) {
    return (int) ((double) rand() / ((double) RAND_MAX + 1) * range);
}

bool BinaryTree::randbool() {
    double result = (double) rand() / ((double) RAND_MAX + 1);
    if (result >= 0.5)
        return true;
    else
        return false;
}

int BinaryTree::getIndexOf(std::vector<Node *> *nodes, Node *node) {
    int index = -1;
    for (int i = 0; i < nodes->size(); i++) {
        if (nodes->at(i) == node) {
            index = i;
            break;
        }
    }
    return index;
}