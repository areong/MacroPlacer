#include "tree/icptree/ICPTree_test.h"
#include <iostream>
#include <vector>
#include "model/Macro.h"
#include "model/Floorplan.h"
#include "model/sa/CountOfMovableMacrosOutsideDesiredRegion.h"
#include "model/sa/FloorplanState.h"
#include "sa/AnnealingScheduleRatioDecrease.h"
#include "sa/CostFunctionGroup.h"
#include "sa/OperationSet.h"
#include "sa/SimulatedAnnealing.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/TraversalTaskPrintIdAndIdentity.h"
#include "tree/icptree/sa/AspectRatio.h"
#include "tree/icptree/sa/BoundingBoxArea.h"
#include "tree/icptree/sa/ChangeCorner0PositionRandomly.h"
#include "tree/icptree/sa/ChangeRandomEmptyNodeWidthRandomly.h"
#include "tree/icptree/sa/ChangeRandomMacroNodeSpacingRandomly.h"
#include "tree/icptree/sa/ChangeRandomMacroNodeVerticalDisplacementRandomly.h"
#include "tree/icptree/sa/InsertEmptyNodeRandomly.h"
#include "tree/icptree/sa/InteriorRegionArea.h"
#include "tree/icptree/sa/MoveCornerRandomly.h"
#include "tree/icptree/sa/RefreshWindow.h"
#include "tree/icptree/sa/RemoveAndInsertLeftNodeRandomly.h"
#include "tree/icptree/sa/RemoveAndInsertRightNodeRandomly.h"
#include "tree/icptree/sa/RemoveEmptyNodeRandomly.h"
#include "tree/icptree/sa/SwapNodesRandomly.h"
#include "tree/icptree/sa/TotalWirelength.h"
#include "utils/Utils.h"
#include "view/FloorplanWindow.h"

/*
Create a Floorplan with random Macros, MacroNodes and ICPTree.
*/
Floorplan *createFloorplanRandomly();

/*
Create a Floorplan with random Macros, MacroNodes and ICPTree.
Please call these three lines before calling this function:
    std::vector<Macro *> *macros = new std::vector<Macro *>();
    std::vector<MacroNode *> *macroNodes = new std::vector<MacroNode *>();
    ICPTree *tree = new ICPTree();
*/
Floorplan *createFloorplanRandomly(std::vector<Macro *> *macros,
    std::vector<MacroNode *> *macroNodes, ICPTree *icpTree);

void displayFloorplan(Floorplan *floorplan);

void deleteMacrosMacroNodesAndTree(std::vector<Macro *> *macros, 
    std::vector<MacroNode *> *macroNodes, ICPTree *tree);

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
    
    std::cout << "Initial01. Root and its right Nodes will not be traversed.\n\tExpected: 1c 8c 9n 5c 4n 2n 3n 0c 6n 7n\n\tResult:   ";
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
    
    std::cout << "Initial02\n\tExpected: -1c -1c 5c 4n 2n 3n 8n 1n 9n 0c 6n 7n\n\tResult:   ";
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
    std::cout << "swap 3 and 5\n\tExpected: -1c -1c 3c 4n 2n 5n 8n 1n 9n 0c 6n 7n\n\tResult:   ";
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
    std::cout << "swap 5 and 8\n\tExpected: -1c -1c 3c 4n 2n 8n 5n 1n 9n 0c 6n 7n\n\tResult:   ";
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
    std::cout << "move 4 to left of 3\n\tExpected: -1c 4b -1c 3c 8n 2n 1n 5n 9n 0c 6n 7n\n\tResult:   ";
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
    std::cout << "move 0 to right of 4\n\tExpected: -1c 4b -1c 0n 3c 8n 2n 1n 5n 9n 6c 7n\n\tResult:   ";
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
    std::cout << "\tExpected: -1c 4b 1b -1c 0n 7b 3c 8n 2n 5n 9n 6c\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->moveCorner(1, false);
    std::cout << "move Corner 1 backward\n";
    std::cout << "\tExpected: -1c 1b -1c 7b 3b 4c 0n 8n 2n 5n 9n 6c\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    tree->assignSwitch(nodes->at(7));
    std::cout << "assign 7 as Switch\n";
    std::cout << "\tExpected: -1c 1b -1c 3b 8n 2n 5n 9n 4c 0n 7s 6c\n\tResult:   ";
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
    std::cout << "\tExpected: -1c 1b -1c 4b 0n -1c 7b -1b 3s 8n 2n 5n 9n 6c\n\tResult:   ";
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
    std::cout << "\tExpected: -1c 1c 4c 0n 7b -1b 3s 8n 2n 5n 9n 6c\n\tResult:   ";
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
    std::cout << "\tExpected: 1b -1c 8c -1b 4c 0n -1b 3s 5n 2n 9n 7s 6c\n\tResult:   ";
    tree->traverseAll(task);
    std::cout << "\n";

    // Have checked removing empty Node at 7, 3 or 1. No error occured in all.
    tree->removeEmptyNode(dynamic_cast<MacroNode *>(nodes->at(1)->getLeftNode()));
    std::cout << "remove empty Node at 1's left\n";
    std::cout << "\tExpected: 1c 8c -1b 4c 0n -1b 3s 5n 2n 9n 7s 6c\n\tResult:   ";
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

void testICPTree_placeMacrosNoNormalNorSwitch() {
    std::vector<Macro *> *macros = new std::vector<Macro *>();
    macros->push_back(new Macro(4, 3)); // Corner 0
    macros->push_back(new Macro(3, 3));
    macros->push_back(new Macro(2, 2));
    macros->push_back(new Macro(2, 3)); // Corner 1
    macros->push_back(new Macro(2, 3));
    macros->push_back(new Macro(2, 3));
    macros->push_back(new Macro(3, 2));
    macros->push_back(new Macro(1, 2)); // Corner 2
    macros->push_back(new Macro(1, 2));
    macros->push_back(new Macro(2, 3));
    macros->push_back(new Macro(3, 2));
    macros->push_back(new Macro(2, 2)); // Corner 3
    macros->push_back(new Macro(1, 2));
    macros->push_back(new Macro(1, 3));
    macros->push_back(new Macro(3, 3));
    macros->push_back(new Macro(2, 1));

    std::vector<MacroNode *> *macroNodes = new std::vector<MacroNode *>();
    for (int i = 0; i < macros->size(); i++) {
        macroNodes->push_back(new MacroNode(macros->at(i)));
    }

    macroNodes->at(0)->setVerticalDisplacement(0); // Corner 0
    macroNodes->at(1)->setVerticalDisplacement(1);
    macroNodes->at(2)->setVerticalDisplacement(0);
    macroNodes->at(3)->setVerticalDisplacement(1); // Corner 1
    macroNodes->at(4)->setVerticalDisplacement(-1);
    macroNodes->at(5)->setVerticalDisplacement(0);
    macroNodes->at(6)->setVerticalDisplacement(-4);
    macroNodes->at(7)->setVerticalDisplacement(0); // Corner 2
    macroNodes->at(8)->setVerticalDisplacement(1);
    macroNodes->at(9)->setVerticalDisplacement(-3);
    macroNodes->at(10)->setVerticalDisplacement(-8);
    macroNodes->at(11)->setVerticalDisplacement(-3); // Corner 3
    macroNodes->at(12)->setVerticalDisplacement(1);
    macroNodes->at(13)->setVerticalDisplacement(1);
    macroNodes->at(14)->setVerticalDisplacement(2);
    macroNodes->at(15)->setVerticalDisplacement(2);

    ICPTree *tree = new ICPTree();
    for (int i = 0; i < macroNodes->size(); i++) {
        tree->addNode(macroNodes->at(i));
    }
    tree->setRoot(macroNodes->at(0));
    tree->setCorner0Position(0, 0);

    // MacroNodes on branches
    for (int i = 1; i < 16; i++) {
        tree->insertLeftNode(macroNodes->at(i), macroNodes->at(i - 1));
    }
    // Set as CornerNode or BranchNode.
    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 3 || i == 7 || i == 11) {
            macroNodes->at(i)->setAsCornerNode();
        } else {
            macroNodes->at(i)->setAsBranchNode();
        }
    }

    // Place
    tree->placeMacrosAssumingNoSwitch();

    // Output
    // Figure: draw grid lines, with x/y ratio 2 (x zooms in 2 times).
    //  15+---+                       
    //  +-+---+       +-----+   +---+ 
    //  |     +-------+     |   |   | 
    //  | 14  |       |  1  +---+ 3 | 
    //  +---+-+   0   +-----+ 2 +---+ 
    //      | +-------+     +---+   | 
    //    13| |                 | 4 | 
    //      +-+ +-+             +---+ 
    //        12| |             |   | 
    //          +-+-+           | 5 | 
    //          |11 |   +-----+ +---+ 
    //          +---+   |  6  |       
    //              +---+-+---+ +-+   
    //              | 10  |   +-+7|   
    //              +-----+ 9 |8+-+   
    //                    +---+-+     
    std::cout << "Place Macros\n\tExpected output:\n"
              << "\t\ti\tx\ty\tverticalDisplacement\n"
              << "\t\t0\t0\t0\t0\n"
              << "\t\t1\t4\t1\t1\n"
              << "\t\t2\t7\t0\t0\n"
              << "\t\t3\t9\t1\t1\n"
              << "\t\t4\t9\t-2\t0\n"
              << "\t\t5\t9\t-5\t0\n"
              << "\t\t6\t5\t-7\t-4\n"
              << "\t\t7\t9\t-9\t0\n"
              << "\t\t8\t8\t-10\t1\n"
              << "\t\t9\t6\t-10\t0\n"
              << "\t\t10\t3\t-9\t0\n"
              << "\t\t11\t1\t-6\t-3\n"
              << "\t\t12\t1\t-4\t1\n"
              << "\t\t13\t-1\t-2\t3\n"
              << "\t\t14\t-3\t1\t3\n"
              << "\t\t15\t-2\t4\t3\n";
    std::cout << "\tResult:\n";
    for (int i = 0; i < 16; i++) {
        Macro *macro = macroNodes->at(i)->getMacro();
        std::cout << "\t\t" << i
                  << "\t" << macro->getXStart()
                  << "\t" << macro->getYStart()
                  << "\t" << macroNodes->at(i)->getVerticalDisplacement() << "\n";
    }

    std::cout << "maxX, minX, maxY, minY: " << tree->getMaxX() << ", "
              << tree->getMinX() << ", " << tree->getMaxY() << ", "
              << tree->getMinY() << "\n";

    //tree->swapNodes(macroNodes->at(2), macroNodes->at(3));
    //tree->removeNode(macroNodes->at(1), true);
    //tree->insertRightNode(macroNodes->at(1), macroNodes->at(0));
    //tree->swapNodes(macroNodes->at(1), macroNodes->at(4));
    //tree->insertEmptyNode(macroNodes->at(0));
    //tree->insertEmptyNode(macroNodes->at(1));
    //tree->insertEmptyNode(macroNodes->at(2));
    //tree->removeNode(macroNodes->at(0), true);
    //for (int i = 0; i < 0; i++) {
    //    tree->insertEmptyNodeRandomly();
    //}
    tree->placeMacrosAssumingNoSwitch();
    //std::cout << tree->getEmptyNodeInsertableMacroNodeRandomly()->getId() << "\n";
    while (false) {
        tree->removeAndInsertLeftNodeRandomly();
        tree->removeAndInsertRightNodeRandomly();
        tree->swapNodesRandomly();
    }

    // Test memory leak.
    for (int i = 0; i < 100000; i++) {//00000; i++) {
        ICPTree *newICPTree = dynamic_cast<ICPTree *>(tree->copy());
        //TraversalTaskPrintIdAndIdentity *task = new TraversalTaskPrintIdAndIdentity();
        //newICPTree->traverseAll(task);
        //std::cout << "\n";
        //delete task;
        newICPTree->placeMacrosAssumingNoSwitch();
        //newICPTree->insertEmptyNodeRandomly();
        delete tree;
        tree = newICPTree;
    }
    
    // Test MacroNode memory leak.
    //std::vector<MacroNode *> *manyMacroNodes = new std::vector<MacroNode *>();
    //for (int i = 0; i < 100000000; ++i) {
    //    //manyMacroNodes->push_back(new MacroNode());
    //    manyMacroNodes->push_back(0);
    //}
    //for (int i = 0; i < manyMacroNodes->size(); ++i) {
    //    //delete manyMacroNodes->at(i);
    //}
    //delete manyMacroNodes;

    // Test copy memory leak.
    MacroNode *macroNode = new MacroNode();
    ICPTree *anotherICPTree = new ICPTree();
    for (int i = 0; i < macroNodes->size(); i++) {
        anotherICPTree->addNode(macroNodes->at(i));
    }
    anotherICPTree->setRoot(macroNodes->at(0));
    for (int i = 0; i < 000000; ++i) {
        //MacroNode *newMacroNode = dynamic_cast<MacroNode *>(macroNode->copy());
        //delete macroNode;
        //macroNode = newMacroNode;
        ICPTree *newICPTree = dynamic_cast<ICPTree *>(anotherICPTree->copy());
        delete anotherICPTree;
        anotherICPTree = newICPTree;
    }

    ICPTree *newICPTree = dynamic_cast<ICPTree *>(anotherICPTree->copy());
    delete tree;
    tree = newICPTree;

    tree->placeMacrosAssumingNoSwitch();

    // Display
    Floorplan *floorplan = new Floorplan(macros, tree);
    displayFloorplan(floorplan);
    //FloorplanWindow *window = FloorplanWindow::createInstance(floorplan);
    //window->setWindowSize(1024, 768);
    //window->setXYRangeByFloorplan();
    //window->initialize();
    //while (true) {
    //    int dummy = 0;
    //    for (int i = 0; i < 1000000; i++) {
    //        dummy += 1;
    //    }
    //    ICPTree *newICPTree = dynamic_cast<ICPTree *>(tree->copy());
    //    delete tree;
    //    tree = newICPTree;
    //    floorplan->setICPTree(tree);
    //    tree->removeAndInsertLeftNodeRandomly();
    //    tree->removeAndInsertRightNodeRandomly();
    //    //tree->swapNodesRandomly();
    //    tree->moveCornerRandomly();
    //    //tree->insertEmptyNodeRandomly();
    //    //tree->removeEmptyNodeRandomly();
    //    //tree->changeRandomEmptyNodeWidthRandomly();
    //    //tree->changeRandomMacroNodeVerticalDisplacementRandomly();
    //    //tree->changeCorner0PositionRandomly();
    //    tree->placeMacrosAssumingNoSwitch();
    //    //std::cout << " " << macros->at(0)->getXStart() << "\n";
    //    //std::cout << " " << floorplan->getMacros()->at(0)->getXStart() << ".\n";
    //    window->runMainLoopEvent();
    //}

    deleteMacrosMacroNodesAndTree(macros, macroNodes, tree);
}

void testICPTree_placeMacrosRandomlyNoSwitch() {
    std::vector<Macro *> *macros = new std::vector<Macro *>();
    std::vector<MacroNode *> *macroNodes = new std::vector<MacroNode *>();
    ICPTree *tree = new ICPTree();
    Floorplan *floorplan = createFloorplanRandomly(macros, macroNodes, tree);
    //icpTree->initializeRandomly();
    //icpTree->setCorner0Position(0, 0);
    tree->initializeBalancedICPTreeRandomly(0, 0, 100, 100, 4000);
    floorplan->createBins(-400, -400, 400, 400, 40, 40);
    FloorplanState *floorplanState = new FloorplanState(floorplan);
    //std::vector<Macro *> *macros = floorplan->getMacros();
    //ICPTree *tree = floorplan->getICPTree();
    //std::vector<MacroNode *> *macroNodes = floorplan->getMacroNodes();

    for (int i = 0; i < 0; i++) {
        tree->insertEmptyNodeRandomly();
    }

    TraversalTaskPrintIdAndIdentity *task = new TraversalTaskPrintIdAndIdentity();
    tree->traverseAll(task);

    // Test memory leak.
    for (int i = 0; i < 00000; i++) {//00000; i++) {
        //ICPTree *newICPTree = dynamic_cast<ICPTree *>(tree->copy());
        //delete tree;
        //tree = newICPTree;
        FloorplanState *newFloorplanState = dynamic_cast<FloorplanState *>(floorplanState->copy());
        delete floorplanState;
        floorplanState = newFloorplanState;
        tree = floorplanState->getICPTree();
        tree->removeAndInsertLeftNodeRandomly();
        tree->removeAndInsertRightNodeRandomly();
        tree->moveCornerRandomly();
        tree->changeRandomMacroNodeVerticalDisplacementRandomly();
        tree->placeMacrosAssumingNoSwitch();
        floorplan->setICPTree(tree);
        floorplan->clearBinsMovableMacros();
        floorplan->addMovableMacrosToBins();
    }

    tree->placeMacrosAssumingNoSwitch();

    // Display
    displayFloorplan(floorplan);
    //FloorplanWindow *window = FloorplanWindow::createInstance(floorplan);
    //window->setWindowSize(1024, 768);
    //window->setXYRangeByFloorplan();
    //window->initialize();
    //window->runMainLoopEvent();
    //while (true) {
    //    int dummy = 0;
    //    for (int i = 0; i < 10000000; i++) {
    //        dummy += 1;
    //    }
    //    tree->removeAndInsertLeftNodeRandomly();
    //    tree->removeAndInsertRightNodeRandomly();
    //    //tree->swapNodesRandomly();
    //    tree->moveCornerRandomly();
    //    //tree->insertEmptyNodeRandomly();
    //    //tree->removeEmptyNodeRandomly();
    //    //tree->changeRandomEmptyNodeWidthRandomly();
    //    //tree->changeRandomMacroNodeVerticalDisplacementRandomly();
    //    //tree->changeCorner0PositionRandomly();
    //    tree->placeMacrosAssumingNoSwitch();
    //    //std::cout << " " << macros->at(0)->getXStart() << "\n";
    //    //std::cout << " " << floorplan->getMacros()->at(0)->getXStart() << ".\n";
    //    window->runMainLoopEvent();
    //}

    deleteMacrosMacroNodesAndTree(macros, macroNodes, tree);
}

void testICPTree_anneal(int argc, char **argv) {
    if (argc < 2) {
        return;
    }
    Floorplan *floorplan = Floorplan::createFromAuxFiles(argv[1]);
    ICPTree *icpTree = new ICPTree(floorplan->getMovableMacros());
    floorplan->setICPTree(icpTree);

    //Floorplan *floorplan = createFloorplanRandomly();
    //ICPTree *icpTree = floorplan->getICPTree();

    //int targetInteriorRegionArea = 6000;
    int targetInteriorRegionArea = (int) (floorplan->calculateCellsArea());

    //icpTree->initializeBalancedICPTreeRandomly(0, 0, 100, 100, targetInteriorRegionArea);
    icpTree->initializeBalancedICPTreeRandomly(500, 500, 11000, 11000, targetInteriorRegionArea);
    //floorplan->createBins(-100, -100, 200, 200, 25, 25);
    floorplan->createBins(-10000, -10000, 20000, 20000, 1000, 1000);
    //floorplan->setDesiredRegion(0, 0, 100, 100);
    floorplan->setDesiredRegion(500, 500, 11000, 11000);
    floorplan->getICPTree()->placeMacrosAssumingNoSwitch(); // Place at first to calculate cost.
    //displayFloorplan(floorplan);
    FloorplanState *floorplanState = new FloorplanState(floorplan);
    std::cout << "boundingBoxArea: " << floorplanState->getICPTree()->getBoundingBoxArea() << "\n";

    // Operations
    RemoveAndInsertLeftNodeRandomly *removeAndInsertLeftNodeRandomly = new RemoveAndInsertLeftNodeRandomly();
    RemoveAndInsertRightNodeRandomly *removeAndInsertRightNodeRandomly = new RemoveAndInsertRightNodeRandomly();
    MoveCornerRandomly *moveCornerRandomly = new MoveCornerRandomly();
    InsertEmptyNodeRandomly *insertEmptyNodeRandomly = new InsertEmptyNodeRandomly();
    RemoveEmptyNodeRandomly *removeEmptyNodeRandomly = new RemoveEmptyNodeRandomly();
    ChangeCorner0PositionRandomly *changeCorner0PositionRandomly = new ChangeCorner0PositionRandomly();
    ChangeRandomEmptyNodeWidthRandomly *changeRandomEmptyNodeWidthRandomly = new ChangeRandomEmptyNodeWidthRandomly();
    ChangeRandomMacroNodeSpacingRandomly *changeRandomMacroNodeSpacingRandomly = new ChangeRandomMacroNodeSpacingRandomly();
    ChangeRandomMacroNodeVerticalDisplacementRandomly *changeRandomMacroNodeVerticalDisplacementRandomly = new ChangeRandomMacroNodeVerticalDisplacementRandomly();
    floorplan->getICPTree()->setChangeRangeOfEmptyNodeWidth(1);
    floorplan->getICPTree()->setChangeRangeOfVerticalDisplacement(100); // 1000
    floorplan->getICPTree()->setChangeRangeOfSpacing(100);
    floorplan->getICPTree()->setChangeRangeOfCorner0Position(100);
    OperationSet *operationSet = new OperationSet();
    operationSet->addOperation(removeAndInsertLeftNodeRandomly);
    operationSet->addOperation(removeAndInsertRightNodeRandomly);
    operationSet->addOperation(moveCornerRandomly);
    //operationSet->addOperation(insertEmptyNodeRandomly);
    //operationSet->addOperation(removeEmptyNodeRandomly);
    //operationSet->addOperation(changeRandomEmptyNodeWidthRandomly);
    operationSet->addOperation(changeRandomMacroNodeVerticalDisplacementRandomly);
    operationSet->addOperation(changeRandomMacroNodeSpacingRandomly);
    operationSet->addOperation(changeCorner0PositionRandomly);

    //for (int i = 0; i < 1000; i++) {
    //    operationSet->operate(floorplanState);
    //}

    // CostFunctions
    InteriorRegionArea *interiorRegionArea = new InteriorRegionArea(targetInteriorRegionArea);
    int targetBoundingBoxArea = floorplan->calculateMacrosArea() + targetInteriorRegionArea;
    std::cout << "targetBoundingBoxArea: " << targetBoundingBoxArea << "\n";
    BoundingBoxArea *boundingBoxArea = new BoundingBoxArea(targetBoundingBoxArea);
    AspectRatio *aspectRatio = new AspectRatio(1);
    TotalWirelength *totalWirelength = new TotalWirelength();
    CountOfMovableMacrosOutsideDesiredRegion *countOfMovableMacrosOutsideDesiredRegion = new CountOfMovableMacrosOutsideDesiredRegion();
    CostFunctionGroup *costFunctionGroup = new CostFunctionGroup();
    costFunctionGroup->addCostFunction(boundingBoxArea, 1);
    costFunctionGroup->addCostFunction(interiorRegionArea, 1);
    costFunctionGroup->addCostFunction(aspectRatio, 1);
    costFunctionGroup->addCostFunction(totalWirelength, 1);
    costFunctionGroup->addCostFunction(countOfMovableMacrosOutsideDesiredRegion, 1);
    costFunctionGroup->normalizeWeights();
    FloorplanState *copiedFloorplanState = dynamic_cast<FloorplanState *>(floorplanState->copy());
    costFunctionGroup->normalizeCosts(copiedFloorplanState, operationSet, 1000);
    delete copiedFloorplanState;

    AnnealingScheduleRatioDecrease *annealingScheduleRatioDecrease = new AnnealingScheduleRatioDecrease(0.9);
    SimulatedAnnealing *simulatedAnnealing = new SimulatedAnnealing();
    simulatedAnnealing->setOperation(operationSet);
    simulatedAnnealing->setCostFunction(costFunctionGroup);
    simulatedAnnealing->setAnnealingSchedule(annealingScheduleRatioDecrease);

    copiedFloorplanState = dynamic_cast<FloorplanState *>(floorplanState->copy());
    annealingScheduleRatioDecrease->initializeTemperature(copiedFloorplanState, 1000, 0.85);
    std::cout << "initialTemperature: " << annealingScheduleRatioDecrease->getTemperature() << "\n";
    delete copiedFloorplanState;

    //// Test memory leak.
    //ICPTree *icpTree = floorplan->getICPTree();
    //for (int i = 0; i < 200000; i++) {//00000; i++) {
    //    ICPTree *newICPTree = dynamic_cast<ICPTree *>(icpTree->copy());
    //    //TraversalTaskPrintIdAndIdentity *task = new TraversalTaskPrintIdAndIdentity();
    //    //newICPTree->traverseAll(task);
    //    //std::cout << "\n";
    //    //delete task;
    //    //newICPTree->placeMacrosAssumingNoSwitch();
    //    delete icpTree;
    //    icpTree = newICPTree;
    //}

    // Window
    FloorplanWindow *window = FloorplanWindow::createInstance(floorplan);
    window->setWindowSize(1024, 768);
    window->setXYRangeByFloorplan();
    window->initialize();
    window->runMainLoopEvent();
    RefreshWindow *refreshWindow = new RefreshWindow(window, floorplan);
    simulatedAnnealing->addTemperatureListener(refreshWindow);

    //for (int i = 0; i < 100000; i++) {
    //    //for (int j = 0; j < 1000000; j++) {
    //    //    int n = 1 + 1;
    //    //}
    //    FloorplanState *newFloorplanState = dynamic_cast<FloorplanState *>(floorplanState->copy());
    //    //std::cout << "\n";
    //    //TraversalTaskPrintIdAndIdentity *task = new TraversalTaskPrintIdAndIdentity();
    //    //newFloorplanState->getICPTree()->traverseAll(task);
    //    //delete task;
    //    operationSet->operate(newFloorplanState);
    //    delete floorplanState;
    //    floorplanState = newFloorplanState;
    //    window->runMainLoopEvent();
    //}

    floorplanState->getICPTree()->placeMacrosAssumingNoSwitch();
    //displayFloorplan(floorplan);
    simulatedAnnealing->anneal(floorplanState, 1000, 0.000001, 0.99, 1200);
    FloorplanState *bestFloorplanState = dynamic_cast<FloorplanState *>(simulatedAnnealing->getBestState());
    std::cout << "finalTemperature: " << annealingScheduleRatioDecrease->getTemperature() << "\n";
    bestFloorplanState->doAfterBeingOperated();
    bestFloorplanState->doBeforeCalculatingCost();
    std::cout << "boundingBoxArea: " << bestFloorplanState->getICPTree()->getBoundingBoxArea() << "\n";
    std::cout << "interiorRegionArea: " << bestFloorplanState->getICPTree()->getInteriorRegionArea() << "\n";
    std::cout << "aspectRatio: " << bestFloorplanState->getICPTree()->getBoundingBoxAspectRatio() << "\n";
    std::cout << "countOutside: " << bestFloorplanState->getFloorplan()->countMovableMacrosOutsideDesiredRegion() << "\n";
}

void testICPTree(int argc, char **argv) {
    //testICPTree_intialize01();
    //testICPTree_intialize02();
    //testICPTree_placeMacrosNoNormalNorSwitch();
    //testICPTree_placeMacrosRandomlyNoSwitch();
    testICPTree_anneal(argc, argv);
}

// private

Floorplan *createFloorplanRandomly() {
    std::vector<Macro *> *macros = new std::vector<Macro *>();
    ICPTree *icpTree = new ICPTree();
    std::vector<MacroNode *> *macroNodes = new std::vector<MacroNode *>();
    return createFloorplanRandomly(macros, macroNodes, icpTree);
}

Floorplan *createFloorplanRandomly(std::vector<Macro *> *macros,
    std::vector<MacroNode *> *macroNodes, ICPTree *icpTree) {
    for (int i = 0; i < 40; i++) {
        macros->push_back(new Macro(Utils::randint(1, 20), Utils::randint(1, 20)));
    }
    for (int i = 0; i < macros->size(); i++) {
        MacroNode *macroNode = new MacroNode(macros->at(i));
        macroNode->setVerticalDisplacement(0);//Utils::randint(-50, 51));
        macroNodes->push_back(macroNode);
        icpTree->addNode(macroNode);
    }
    return new Floorplan(macros, icpTree);
}

void displayFloorplan(Floorplan *floorplan) {
    FloorplanWindow *window = FloorplanWindow::createInstance(floorplan);
    window->setWindowSize(1024, 768);
    window->setXYRangeByFloorplan();
    window->initialize();
    window->runMainLoop();
}

void deleteMacrosMacroNodesAndTree(std::vector<Macro *> *macros, 
    std::vector<MacroNode *> *macroNodes, ICPTree *tree) {
    delete tree;
    delete macroNodes;
    for (int i = 0; i < macros->size(); i++) {
        delete macros->at(i);
    }
    delete macros;
}