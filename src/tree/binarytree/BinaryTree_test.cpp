#include "tree/binarytree/BinaryTree_test.h"
#include <iostream>
#include <vector>
#include "tree/binarytree/BinaryTree.h"
#include "tree/binarytree/Node.h"
#include "tree/binarytree/NextNodesBehaviorRightFirst.h"
#include "tree/binarytree/TraversalTaskPrintId.h"

void testBinaryTree() {
    // Create Nodes.
    std::vector<Node *> *nodes = new std::vector<Node *>();
    for (int i = 0; i < 11; i++)
        nodes->push_back(new Node());
    // Create BinaryTree.
    BinaryTree *binaryTree = new BinaryTree();
    // Add Nodes.
    // Since the id 0 is BinaryTree.head, ignore it.
    for (int i = 1; i < nodes->size(); i++)
        binaryTree->addNode(nodes->at(i));
    // Connect Nodes.
    // 1 - 3 -
    //   |   L 7 - 8 - 9
    //   |       |   L 10
    //   |       L
    //   L 2 - 4 - 6
    //       |   L
    //       L 5
    binaryTree->setRoot(nodes->at(1));
    binaryTree->insertLeftNode(nodes->at(2), nodes->at(1));
    binaryTree->insertRightNode(nodes->at(3), nodes->at(1));
    binaryTree->insertLeftNode(nodes->at(5), nodes->at(2));
    binaryTree->insertRightNode(nodes->at(4), nodes->at(2));
    binaryTree->insertRightNode(nodes->at(6), nodes->at(4));
    binaryTree->insertLeftNode(nodes->at(7), nodes->at(3));
    binaryTree->insertRightNode(nodes->at(8), nodes->at(7));
    binaryTree->insertLeftNode(nodes->at(10), nodes->at(8));
    binaryTree->insertRightNode(nodes->at(9), nodes->at(8));

    // Prepare printing id.
    TraversalTaskPrintId *taskPrintId = new TraversalTaskPrintId();
    // Print id in dfs.
    std::cout << "Initial\n\tExpected: 1 2 5 4 6 3 7 8 10 9\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    binaryTree->swapNodes(nodes->at(3), nodes->at(4));
    std::cout << "Swap 3 and 4\n\tExpected: 1 2 5 3 6 4 7 8 10 9\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    binaryTree->swapNodes(nodes->at(2), nodes->at(3));
    std::cout << "Swap 2 and 3\n\tExpected: 1 3 5 2 6 4 7 8 10 9\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    // 4 - 7 -
    //   |   L 8 - 9 -
    //   |       |   L 10
    //   |       L
    //   L 3 - 2 - 6
    //       |   L
    //       L 5
    binaryTree->removeNode(nodes->at(1), false);
    std::cout << "Remove 1, replace with right nodes\n\tExpected: 4 3 5 2 6 7 8 9 10\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    // 4 - 7 -
    //   |   L 8 - 9 -
    //   |       |   L 10
    //   |       L
    //   L 3 - 2 - 6
    //       |   L
    //       L 1 -
    //           L 5
    binaryTree->insertLeftNode(nodes->at(1), nodes->at(3));
    std::cout << "Insert 1 as the left node of 3\n\tExpected: 4 3 1 5 2 6 7 8 9 10\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    nodes->at(4)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    nodes->at(3)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    nodes->at(1)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    nodes->at(5)->setNextNodesBehavior(new NextNodesBehaviorRightFirst());
    std::cout << "Let 4, 3, 1 and 5 to return right node first in traversal\n\tExpected: 4 7 8 9 10 3 2 6 1 5\n\tResult:   ";
    binaryTree->traverseDfs(binaryTree->getRoot(), taskPrintId);
    std::cout << "\n";

    BinaryTree *copiedBinaryTree = binaryTree->copy();
    delete binaryTree;
    std::cout << "Copy, delete the original, and traverse the copy\n\tExpected: 4 7 8 9 10 3 2 6 1 5\n\tResult:   ";
    copiedBinaryTree->traverseDfs(copiedBinaryTree->getRoot(), taskPrintId);
    std::cout << "\n";
}