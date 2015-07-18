#include "tree/icptree/contour/Contour_test.h"
#include <iostream>
#include <vector>
#include "model/Macro.h"
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/contour/Edge.h"
#include "tree/icptree/contour/Contour.h"
#include "tree/icptree/contour/TopContour.h"
#include "tree/icptree/contour/BottomContour.h"
#include "tree/icptree/contour/RightContour.h"
#include "tree/icptree/contour/LeftContour.h"

void testContour() {
    testContourBasic();
}

void testContourBasic() {
    std::vector<Macro *> *macros = new std::vector<Macro *>();
    macros->push_back(new Macro(9, 6)); // B* tree
    macros->push_back(new Macro(6, 8));
    macros->push_back(new Macro(3, 6));
    macros->push_back(new Macro(3, 7));
    macros->push_back(new Macro(6, 5));
    macros->push_back(new Macro(12, 2));
    macros->push_back(new Macro(4, 3)); // Place at x

    std::vector<MacroNode *> *macroNodes = new std::vector<MacroNode *>();
    for (int i = 0; i < macros->size(); i++) {
        macroNodes->push_back(new MacroNode(macros->at(i)));
    }

    // Place the Macros as if they are packed by the following B* tree:
    // 0 - 2 - 5
    // |   |
    // 1   3
    //     |
    //     4
    // which is the example given in chapter 10.2.3.2, "From a B*-tree
    // to its floorplan", EDA (Tung-Chieh Chen).
    // Each step of placing Macros can be tested by commenting part of
    // the following lines.
    Contour *contour = new TopContour();
    contour->initialize(0, 0);
    //contour->placeMacroOnEdgeWithPackingForward(macroNodes->at(0), contour->getTail());
    //contour->placeMacroOnEdgeWithPackingForward(macroNodes->at(1), contour->getMacroNodeTopEdge(macroNodes->at(0))->getBackEdge());
    //contour->placeMacroOnTopOfMacroWithPackingForward(macroNodes->at(2), macroNodes->at(0));
    //contour->placeMacroOnEdgeWithPackingForward(macroNodes->at(3), contour->getMacroNodeTopEdge(macroNodes->at(2))->getBackEdge());
    //contour->placeMacroOnEdgeWithPackingForward(macroNodes->at(4), contour->getMacroNodeTopEdge(macroNodes->at(3))->getBackEdge());
    //contour->placeMacroOnTopOfMacroWithPackingForward(macroNodes->at(5), macroNodes->at(2));
    
    contour->placeMacroOnEdgeWithPackingBackward(macroNodes->at(0), contour->getHead());
    contour->placeMacroOnEdgeWithPackingBackward(macroNodes->at(1), contour->getMacroNodeTopEdge(macroNodes->at(0))->getFrontEdge());
    contour->placeMacroOnTopOfMacroWithPackingBackward(macroNodes->at(2), macroNodes->at(0));
    contour->placeMacroOnEdgeWithPackingBackward(macroNodes->at(3), contour->getMacroNodeTopEdge(macroNodes->at(2))->getFrontEdge());
    contour->placeMacroOnEdgeWithPackingBackward(macroNodes->at(4), contour->getMacroNodeTopEdge(macroNodes->at(3))->getFrontEdge());
    contour->placeMacroOnTopOfMacroWithPackingBackward(macroNodes->at(5), macroNodes->at(2));
    
    // Place at x.
    //contour->placeMacroAtXWithPackingForward(macroNodes->at(6), 15);
    contour->placeMacroAtXWithPackingBackward(macroNodes->at(6), -3);

    contour->printEdges();

    delete contour;
    for (int i = 0; i < macroNodes->size(); i++) {
        delete macroNodes->at(i);
    }
    for (int i = 0; i < macros->size(); i++) {
        delete macros->at(i);
    }
}

void testContourLegalize() {
    // exteriorTopContour         head>----->--->------>tail
    //                                   6    7    8
    // interiorBottomContour      tail<-----<---<------<head
    //         origin (5, 10)            -7   -3  -6   <== verticalDisplacement
    //                                   /|    |  /|    
    //                                  / |    | / |   <== Edges overlap in x direction
    //                                 /  |    |/  |
    //         origin (29, 0)    -10 -6  -3   -9  -2      -1
    // interiorTopContour    head>-->--->--->---->------->---->tail
    //                             0  1  2     3     4     5
    // exteriorBottomContour tail<--<---<---<----<-------<----<head
    std::vector<Macro *> *macros = new std::vector<Macro *>();
    macros->push_back(new Macro(3, 1)); // TopContour (interior, so as the following)
    macros->push_back(new Macro(4, 1));
    macros->push_back(new Macro(4, 1));
    macros->push_back(new Macro(5, 1));
    macros->push_back(new Macro(8, 1));
    macros->push_back(new Macro(5, 1));
    macros->push_back(new Macro(6, 1)); // BottomContour
    macros->push_back(new Macro(4, 1));
    macros->push_back(new Macro(7, 1));
    macros->push_back(new Macro(1, 5)); // RightContour
    macros->push_back(new Macro(1, 2));
    macros->push_back(new Macro(1, 3));

    std::vector<MacroNode *> *macroNodes = new std::vector<MacroNode *>();
    for (int i = 0; i < macros->size(); i++) {
        macroNodes->push_back(new MacroNode(macros->at(i)));
    }
    macroNodes->at(0)->setVerticalDisplacement(-10); // TopContour
    macroNodes->at(1)->setVerticalDisplacement(-6);
    macroNodes->at(2)->setVerticalDisplacement(-3);
    macroNodes->at(3)->setVerticalDisplacement(-9);
    macroNodes->at(4)->setVerticalDisplacement(-2);
    macroNodes->at(5)->setVerticalDisplacement(-1);
    macroNodes->at(6)->setVerticalDisplacement(-7); // BottomContour
    macroNodes->at(7)->setVerticalDisplacement(-3);
    macroNodes->at(8)->setVerticalDisplacement(-6);
    macroNodes->at(9)->setVerticalDisplacement(3);  // RightContour
    macroNodes->at(10)->setVerticalDisplacement(-13);
    macroNodes->at(11)->setVerticalDisplacement(-10);

    Contour *exteriorTopContour = new TopContour();
    Contour *interiorBottomContour = new BottomContour();
    Contour *exteriorBottomContour = new BottomContour();
    Contour *interiorTopContour = new TopContour();
    exteriorTopContour->initialize(5, 10);
    interiorBottomContour->initialize(5, 10);
    exteriorBottomContour->initialize(29, 0);
    interiorTopContour->initialize(29, 0);

    for (int i = 6; i <= 8; i++) {
        exteriorTopContour->placeMacroOnTailByVerticalDisplacementWithPackingForward(macroNodes->at(i));
        interiorBottomContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(macroNodes->at(i));
    }
    for (int i = 5; i >= 0; i--) {
        exteriorBottomContour->placeMacroOnTailByVerticalDisplacementWithPackingForward(macroNodes->at(i));
        interiorTopContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(macroNodes->at(i));
    }

    //interiorTopContour->legalizeMacrosToABottomContour(interiorBottomContour);
    //interiorBottomContour->legalizeMacrosToABottomContour(interiorTopContour);

    // exteriorLeftContour   tail |    | head    interiorRightContour
    //                        10  ^    v
    //                            | 11 | -10
    //                         7  ^    v
    //                            | 10 | -13
    //                         5  ^    v
    //                            |  9 |  3
    //          origin (0, 0)  0  ^    v
    //                       head |    | tail
    // exteriorBottomContour and interiorTopContour: already created
    Contour *exteriorLeftContour = new LeftContour();
    Contour *interiorRightContour = new RightContour();
    exteriorLeftContour->initialize(0, 0);
    interiorRightContour->initialize(0, 0);
    for (int i = 9; i <= 11; i++) {
        exteriorLeftContour->placeMacroOnTailByVerticalDisplacementWithPackingForward(macroNodes->at(i));
        interiorRightContour->placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(macroNodes->at(i));
    }

    //interiorTopContour->legalizeMacrosToARightContour(interiorRightContour);
    //interiorBottomContour->legalizeMacrosToALeftContour(interiorRightContour);
    //interiorRightContour->legalizeMacrosToARightContour(interiorBottomContour);
    interiorRightContour->legalizeMacrosToALeftContour(interiorTopContour);

    //exteriorTopContour->printEdges();
    //interiorBottomContour->printEdges();
    exteriorBottomContour->printEdges();
    interiorTopContour->printEdges();
    exteriorLeftContour->printEdges();
    interiorRightContour->printEdges();

    delete exteriorTopContour;
    delete interiorBottomContour;
    delete exteriorBottomContour;
    delete interiorTopContour;
    delete exteriorLeftContour;
    delete interiorRightContour;
    for (int i = 0; i < macroNodes->size(); i++) {
        delete macroNodes->at(i);
    }
    for (int i = 0; i < macros->size(); i++) {
        delete macros->at(i);
    }
}