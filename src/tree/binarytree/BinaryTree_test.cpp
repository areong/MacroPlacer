#include "tree/binarytree/BinaryTree_test.h"
#include <iostream>
#include <vector>
#include "tree/binarytree/BinaryTree.h"
#include "tree/binarytree/Node.h"
#include "tree/binarytree/NextNodesBehaviorRightFirst.h"
#include "tree/binarytree/TraversalTaskPrintId.h"

void test();

void testBinaryTree_basic() {
    // Create Nodes.
    std::vector<Node *> *nodes = new std::vector<Node *>();
    for (int i = 0; i < 10; i++)
        nodes->push_back(new Node());
    // Create BinaryTree.
    BinaryTree *binaryTree = new BinaryTree();
    // Add Nodes.
    // Since the id 0 is BinaryTree.head, ignore it.
    for (int i = 0; i < nodes->size(); i++)
        binaryTree->addNode(nodes->at(i));
    // Connect Nodes.
    // 0 - 2 -
    //   |   L 6 - 7 - 8
    //   |       |   L 9
    //   |       L
    //   L 1 - 3 - 5
    //       |   L
    //       L 4
    binaryTree->setRoot(nodes->at(0));
    binaryTree->insertLeftNode(nodes->at(1), nodes->at(0));
    binaryTree->insertRightNode(nodes->at(2), nodes->at(0));
    binaryTree->insertLeftNode(nodes->at(4), nodes->at(1));
    binaryTree->insertRightNode(nodes->at(3), nodes->at(1));
    binaryTree->insertRightNode(nodes->at(5), nodes->at(3));
    binaryTree->insertLeftNode(nodes->at(6), nodes->at(2));
    binaryTree->insertRightNode(nodes->at(7), nodes->at(6));
    binaryTree->insertLeftNode(nodes->at(9), nodes->at(7));
    binaryTree->insertRightNode(nodes->at(8), nodes->at(7));

    // Prepare printing id.
    TraversalTaskPrintId *taskPrintId = new TraversalTaskPrintId();
    // Print id in dfs.
    std::cout << "Initial\n\tExpected: 0 1 4 3 5 2 6 7 9 8\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    binaryTree->swapNodes(nodes->at(2), nodes->at(3));
    std::cout << "Swap 3 and 4\n\tExpected: 0 1 4 2 5 3 6 7 9 8\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    binaryTree->swapNodes(nodes->at(1), nodes->at(2));
    std::cout << "Swap 2 and 3\n\tExpected: 0 2 4 1 5 3 6 7 9 8\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    // 3 - 6 -
    //   |   L 7 - 8 -
    //   |       |   L 9
    //   |       L
    //   L 2 - 1 - 5
    //       |   L
    //       L 4
    binaryTree->removeNode(nodes->at(0), false);
    std::cout << "Remove 0, replace with right nodes\n\tExpected: 3 2 4 1 5 6 7 8 9\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    // 3 - 6 -
    //   |   L 7 - 8 -
    //   |       |   L 9
    //   |       L
    //   L 2 - 1 - 5
    //       |   L
    //       L 0 -
    //           L 4
    binaryTree->insertLeftNode(nodes->at(0), nodes->at(2));
    std::cout << "Insert 0 as the left node of 2\n\tExpected: 3 2 0 4 1 5 6 7 8 9\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    nodes->at(3)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    nodes->at(2)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    nodes->at(0)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    nodes->at(4)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    std::cout << "Let 3, 2, 0 and 4 to return right node first in traversal\n\tExpected: 3 6 7 8 9 2 1 5 0 4\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    BinaryTree *copiedBinaryTree = binaryTree->copy();
    delete binaryTree;
    std::cout << "Copy, delete the original, and traverse the copy\n\tExpected: 3 6 7 8 9 2 1 5 0 4\n\tResult:   ";
    copiedBinaryTree->traverseDfs(copiedBinaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    binaryTree = new BinaryTree();
    for (int i = 0; i < 10; i++)
        binaryTree->addNode(new Node());
    binaryTree->initializeRandomly();
    std::cout << "Create a new BinaryTree and initialize randomly\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    std::cout << "Get a node randomly\n\tResult:   ";
    std::cout << binaryTree->getNodeRandomly()->getId() << "\n";

    binaryTree->removeAndInsertLeftNodeRandomly();
    std::cout << "Remove and insert left Node randomly\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    binaryTree->removeAndInsertRightNodeRandomly();
    std::cout << "Remove and insert right Node randomly\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    binaryTree->swapNodesRandomly();
    std::cout << "Swap Nodes randomly\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";
}

void testBinaryTree_swapRandomly() {
    // Create Nodes.
    std::vector<Node *> *nodes = new std::vector<Node *>();
    for (int i = 0; i < 40; i++)
        nodes->push_back(new Node());
    // Create BinaryTree.
    BinaryTree *binaryTree = new BinaryTree();
    // Add Nodes.
    // Since the id 0 is BinaryTree.head, ignore it.
    for (int i = 0; i < nodes->size(); i++)
        binaryTree->addNode(nodes->at(i));

    binaryTree->initializeRandomly();

    // Test memory leak.
    //for (int i = 0; i < 100000; i++) {
    //    BinaryTree *newBinaryTree = binaryTree->copy();
    //    delete binaryTree;
    //    binaryTree = newBinaryTree;
    //}

    // Test NextNodesBehaviorRightFirst memory leak.
    //std::vector<NextNodesBehaviorRightFirst *> *manyNodes = new std::vector<NextNodesBehaviorRightFirst *>();
    //for (int i = 0; i < 10000000; ++i) {
    //    //manyNodes->push_back(new NextNodesBehaviorRightFirst());
    //    NextNodesBehaviorRightFirst *n = new NextNodesBehaviorRightFirst();
    //    manyNodes->push_back(n);
    //    //delete n;
    //    //manyNodes->push_back(0);
    //}
    //for (int i = 0; i < manyNodes->size(); ++i) {
    //    delete manyNodes->at(i);
    //}
    //delete manyNodes;

    //NextNodesBehaviorRightFirst *manyNodes[1000000];
    //for (int i = 0; i < 1000000; ++i) {
    //    manyNodes[i] = new NextNodesBehaviorRightFirst();
    //}
    //for (int i = 0; i < 1000000; ++i) {
    //    delete manyNodes[i];
    //}
    //delete[] manyNodes;

    // Test copy memory leak.
    Node *node = new Node();
    for (int i = 0; i < 1000000; ++i) {
        //Node *oldNode = node;
        //node = node->copy();
        //delete oldNode;
        BinaryTree *oldBinaryTree = binaryTree;
        binaryTree = binaryTree->copy();
        delete oldBinaryTree;
    }

    //test();

    int a = 0;
    for (int i = 0; i < 1000000000; ++i) {
        a += 1;
    }

    //while (true) {
    //    binaryTree->swapNodesRandomly();
    //}
}

void test() {
    std::vector<NextNodesBehaviorRightFirst *> manyNodes;
    for (int i = 0; i < 10000000; ++i) {
        //manyNodes.push_back(new NextNodesBehaviorRightFirst());
        manyNodes.push_back(0);
    }
    for (int i = 0; i < manyNodes.size(); ++i) {
        //delete manyNodes[i];
    }
    manyNodes.clear();
}

void testBinaryTree() {
    //testBinaryTree_basic();
    testBinaryTree_swapRandomly();
}