#include "tree/icptree/ICPTree_test.h"
#include <iostream>
#include <vector>
#include "model/Macro.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/TraversalTaskPrintIdAndIdentity.h"

void testICPTree_intialize01() {
    ICPTree *tree = new ICPTree();
    std::vector<MacroNode *> *nodes = new std::vector<MacroNode *>();
    for (int i = 0; i < 10; i++)
        nodes->push_back(new MacroNode());
    for (int i = 0; i < 10; i++)
        tree->addNode(nodes->at(i));

    // 0c- 6 - 7
    // |
    // 5c- 4 - 3
    // |   |
    // |   2
    // 8c- 9
    // |
    // 1c
    tree->setRoot(nodes->at(0));
    tree->insertLeftNode(nodes->at(5), nodes->at(0));
    tree->insertRightNode(nodes->at(6), nodes->at(0));
    tree->insertRightNode(nodes->at(7), nodes->at(6));
    tree->insertLeftNode(nodes->at(8), nodes->at(5));
    tree->insertRightNode(nodes->at(4), nodes->at(5));
    tree->insertLeftNode(nodes->at(2), nodes->at(4));
    tree->insertRightNode(nodes->at(3), nodes->at(4));
    tree->insertRightNode(nodes->at(9), nodes->at(8));
    tree->insertLeftNode(nodes->at(1), nodes->at(8));
    tree->initializeMacroNodesOnBranchesRandomly();
    TraversalTaskPrintIdAndIdentity *task = new TraversalTaskPrintIdAndIdentity();
    
    std::cout << "Initial01. Root and its right Nodes will not be traversed.\n\tExpected: 1c 8c 9n 5c 4n 2n 3n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";
    delete tree;
    delete nodes;
}

void testICPTree_intialize02() {
    ICPTree *tree = new ICPTree();
    std::vector<Macro *> *macros = new std::vector<Macro *>();
    for (int i = 0; i < 10; i++)
        macros->push_back(new Macro());
    std::vector<MacroNode *> *nodes = new std::vector<MacroNode *>();
    for (int i = 0; i < 10; i++) {
        MacroNode *macroNode = new MacroNode();
        macroNode->setMacro(macros->at(i));
        nodes->push_back(macroNode);
    }
    for (int i = 0; i < 10; i++)
        tree->addNode(nodes->at(i));

    // 0c- 6 - 7
    // |
    // 5c- 4 - 3 - 1
    // |   |   |   |
    // -1c 2   8   9
    // |
    // -1c
    tree->setRoot(nodes->at(0));
    tree->insertLeftNode(nodes->at(5), nodes->at(0));
    tree->insertRightNode(nodes->at(6), nodes->at(0));
    tree->insertRightNode(nodes->at(7), nodes->at(6));
    tree->insertLeftNode(nodes->at(8), nodes->at(3));
    tree->insertRightNode(nodes->at(4), nodes->at(5));
    tree->insertLeftNode(nodes->at(2), nodes->at(4));
    tree->insertRightNode(nodes->at(3), nodes->at(4));
    tree->insertLeftNode(nodes->at(9), nodes->at(1));
    tree->insertRightNode(nodes->at(1), nodes->at(3));
    tree->initializeMacroNodesOnBranchesRandomly();
    TraversalTaskPrintIdAndIdentity *task = new TraversalTaskPrintIdAndIdentity();
    
    std::cout << "Initial02\n\tExpected: -1c -1c 5c 4n 2n 3n 8n 1n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // 0 - 6 - 7
    // |
    // 3 - 4 - 5 - 1
    // |   |   |   |
    // -1c 2   8   9
    // |
    // -1c
    tree->swapNodes(nodes->at(3), nodes->at(5));
    std::cout << "swap 3 and 5\n\tExpected: -1c -1c 3c 4n 2n 5n 8n 1n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // 0c- 6 - 7
    // |
    // 3c- 4 - 8 - 1
    // |   |   |   |
    // -1c 2   5   9
    // |
    // -1c
    tree->swapNodes(nodes->at(5), nodes->at(8));
    std::cout << "swap 5 and 8\n\tExpected: -1c -1c 3c 4n 2n 8n 5n 1n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // 0c- 6 - 7
    // |
    // 3c- 8 - 1 - 9
    // |   |   |
    // 4   2   5
    // |
    // -1c
    // |
    // -1c
    tree->removeNode(nodes->at(4), false);
    tree->insertLeftNode(nodes->at(4), nodes->at(3));
    std::cout << "move 4 to left of 3\n\tExpected: -1c 4b -1c 3c 8n 2n 1n 5n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // 6c- 7
    // |
    // 3c----- 8 - 1 - 9
    // |       |   |
    // 4 - 0   2   5
    // |
    // -1c
    // |
    // -1c
    tree->removeNode(nodes->at(0), false);
    tree->insertRightNode(nodes->at(0), nodes->at(4));
    std::cout << "move 0 to right of 4\n\tExpected: -1c 4b -1c 0n 3c 8n 2n 1n 5n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // 6c
    // |
    // 7
    // |
    // 3c----- 8 - 5 - 9
    // |       |
    // 4 - 0   2
    // |
    // 1
    // |
    // -1c
    // |
    // -1c
    tree->removeNode(nodes->at(7), true);
    tree->insertLeftNode(nodes->at(7), nodes->at(6));
    tree->removeNode(nodes->at(1), true);
    tree->insertLeftNode(nodes->at(1), nodes->at(4));
    std::cout << "move 7 to left of 6, move 1 to left of 4\n";
    std::cout << "\tExpected: -1c 4b 1b -1c 0n 7b 3c 8n 2n 5n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->moveCorner(1, false);
    std::cout << "move Corner 1 backward\n";
    std::cout << "\tExpected: -1c 1b -1c 7b 3b 4c 0n 8n 2n 5n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->assignSwitch(nodes->at(7));
    std::cout << "assign 7 as Switch\n";
    std::cout << "\tExpected: -1c 1b -1c 3b 8n 2n 5n 9n 4c 0n 7s\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // 6c
    // |
    // 7
    // |
    // -1
    // |
    // 3s----- 8 - 5 - 9
    // |       |
    // 4 - 0   2
    // |
    // -1c
    // |
    // 1
    // |
    // -1c
    // |
    // -1c
    tree->insertEmptyNode(nodes->at(7));
    tree->insertEmptyNode(nodes->at(4));
    tree->moveSwitch(nodes->at(7), false);
    tree->moveCorner(1, false);
    std::cout << "insert empty nodes at 7 and 4. move Switch (7) backward. move Corner 1 backward\n";
    std::cout << "\tExpected: -1c 1b -1c 4b 0n -1c 7b -1b 3s 8n 2n 5n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // 6c
    // |
    // 7
    // |
    // -1
    // |
    // 3s----- 8 - 5 - 9
    // |       |
    // 4c- 0   2
    // |
    // 1c
    // |
    // -1c
    tree->removeEmptyNode(dynamic_cast<MacroNode *>(nodes->at(1)->getLeftNode()));
    tree->removeEmptyNode(dynamic_cast<MacroNode *>(nodes->at(4)->getLeftNode()));
    std::cout << "remove the empty nodes: the left Nodes of 4 and 1\n";
    std::cout << "\tExpected: -1c 1c 4c 0n 7b -1b 3s 8n 2n 5n 9n\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->assignSwitch(nodes->at(7));
    tree->removeNode(nodes->at(8), false);
    tree->insertLeftNode(nodes->at(8), nodes->at(4));
    std::cout << "assign 7 as Switch. move 8 to left of 4\n";
    std::cout << "\tgetNonEmptyBranchNodeRandomly: " << tree->getNonEmptyBranchNodeRandomly()->getId() << "\n";
    std::cout << "\tgetSwitchNodeRandomly: " << tree->getSwitchNodeRandomly()->getId() << "\n";
    std::cout << "\tgetEmptyNodeInsertableMacroNodeRandomly: " << tree->getEmptyNodeInsertableMacroNodeRandomly()->getId() << "\n";
    std::cout << "\tgetEmptyNodeRandomly: " << tree->getEmptyNodeRandomly()->getParentNode()->getId() << "\n";

    tree->moveCorner(2, true);
    tree->insertEmptyNode(nodes->at(3));
    std::cout << "move Corner 2 forward. insert empty Node at 3\n";
    std::cout << "\tExpected: 1b -1c 8c -1b 4c 0n -1b 3s 5n 2n 9n 7s\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // Have checked removing empty Node at 7, 3 or 1. No error occured in all.
    tree->removeEmptyNode(dynamic_cast<MacroNode *>(nodes->at(1)->getLeftNode()));
    std::cout << "remove empty Node at 1's left\n";
    std::cout << "\tExpected: 1c 8c -1b 4c 0n -1b 3s 5n 2n 9n 7s\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->moveCornerRandomly();
    std::cout << "moveCornerRandomly:\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->assignSwitchRandomly();
    std::cout << "assignSwitchRandomly:\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->moveSwitchRandomly();
    std::cout << "moveSwitchRandomly:\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->removeSwitchRandomly();
    std::cout << "removeSwitchRandomly:\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->insertEmptyNodeRandomly();
    std::cout << "insertEmptyNodeRandomly:\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->removeEmptyNodeRandomly();
    std::cout << "removeEmptyNodeRandomly:\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // Copy and delete an ICPTree without MacroNode added.
    ICPTree *newTree = new ICPTree();
    ICPTree *copiedNewTree = dynamic_cast<ICPTree *>(newTree->copy());
    delete newTree;
    delete copiedNewTree;

    // Copy the existing ICPTree, delete the existing and traverse the copied.
    ICPTree *copiedTree = dynamic_cast<ICPTree *>(tree->copy());
    delete tree;
    std::cout << "copy, delete the old and print the copied:\n\tResult:   ";
    copiedTree->traverseAll(task);
    std::cout << "\n";

    // Check whether the macros of the copied ICPTree's MacroNodes remain the same.
    bool result = true;
    for (int i = 0; i < copiedTree->getNodes()->size(); i++) {
        MacroNode *macroNode = dynamic_cast<MacroNode *>(copiedTree->getNodes()->at(i));
        if (macroNode->getMacro() != macros->at(i)) {
            result = false;
            break;
        }
    }
    std::cout << "are the macros remain the same, not being copied?\n";
    std::cout << "\tResult: " << result << "\n";

    //delete tree;  // Double delete causes undefined behaviors.
    delete nodes;
}

void testICPTree() {
    testICPTree_intialize01();
    testICPTree_intialize02();
}