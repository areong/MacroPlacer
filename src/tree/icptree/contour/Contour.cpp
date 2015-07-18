#include "tree/icptree/contour/Contour.h"
#include <iostream>
#include "tree/icptree/MacroNode.h"
#include "tree/icptree/contour/Edge.h"

Contour::Contour() {
    edgesToBeDeleted = new std::vector<Edge *>();
}

Contour::~Contour() {
    // Traverse all Edges, collect Edges whose macroNode is zero,
    // including head, tail and Edges created in Contour methods
    // such as placeMacroAtXWithPackingForward(),
    // and delete them.
    Edge *currentEdge = head;
    while (true) {
        if (currentEdge->getMacroNode() == 0) {
            edgesToBeDeleted->push_back(currentEdge);
        }
        if (currentEdge == tail) {
            break;
        }
        currentEdge = currentEdge->getBackEdge();
    }
    for (int i = 0; i < edgesToBeDeleted->size(); i++) {
        delete edgesToBeDeleted->at(i);
    }
    delete edgesToBeDeleted;
}

void Contour::initialize(int originX, int originY) {
    this->originX = originX;
    this->originY = originY;
    delete head;
    delete tail;
    initializeHeadAndTail(originX, originY);
    head->setBackEdge(tail);
    tail->setFrontEdge(head);
    initializeMaxMinXY();
}

Edge *Contour::getHead() {
    return head;
}

Edge *Contour::getTail() {
    return tail;
}

void Contour::insertEdge(Edge *edge, Edge *position) {
    Edge *positionBack = position->getBackEdge();
    position->setBackEdge(edge);
    edge->setFrontEdge(position);
    edge->setBackEdge(positionBack);
    positionBack->setFrontEdge(edge);
}

void Contour::insertEdgeAtFront(Edge *edge, Edge *position) {
    Edge *positionFront = position->getFrontEdge();
    position->setFrontEdge(edge);
    edge->setBackEdge(position);
    edge->setFrontEdge(positionFront);
    positionFront->setBackEdge(edge);
}

void Contour::removeEdge(Edge *edge) {
    Edge *edgeFront = edge->getFrontEdge();
    Edge *edgeBack = edge->getBackEdge();
    edgeFront->setBackEdge(edgeBack);
    edgeBack->setFrontEdge(edgeFront);
    edge->setFrontEdge(0);
    edge->setBackEdge(0);
    if (edge->getMacroNode() == 0) {
        edgesToBeDeleted->push_back(edge);
    }
}

void Contour::placeMacroOnTailByVerticalDisplacementWithPackingForward(MacroNode *macroNode) {
    Macro *macro = macroNode->getMacro();
    setMacroYStart(macro, addToY(getOriginY(), macroNode->getVerticalDisplacement()));
    setMacroXStart(macro, getEdgeXStart(tail));
    Edge *insertedEdge = createMacroNodeTopEdge(macroNode);
    setEdgeXStart(tail, getEdgeXEnd(insertedEdge));
    insertEdge(insertedEdge, tail->getFrontEdge());
    updateMaxY(getEdgeYEnd(insertedEdge));
    updateMinY(getMacroYStart(macro));
    updateMaxX(getEdgeXEnd(insertedEdge));
    updateMinX(getEdgeXStart(insertedEdge));
}

void Contour::placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(MacroNode *macroNode) {
    Macro *macro = macroNode->getMacro();
    setMacroXEnd(macro, getEdgeXEnd(head));
    Edge *insertedEdge = createMacroNodeTopEdge(macroNode);
    setEdgeXEnd(head, getEdgeXStart(insertedEdge));
    insertEdge(insertedEdge, head);
    updateMaxY(getEdgeYEnd(insertedEdge));
    updateMinY(getMacroYStart(macro));
    updateMaxX(getEdgeXEnd(insertedEdge));
    updateMinX(getEdgeXStart(insertedEdge));
}

void Contour::setTailYToTheLastMacroYStart() {
    Macro *macro = tail->getFrontEdge()->getMacroNode()->getMacro();
    setEdgeYEnd(tail, getMacroYStart(macro));
}

void Contour::legalizeMacrosToABottomContour(Contour *bottomContour) {
    // BottomContour    tail<-----<---<------<---<head
    //                         /|    |  /|    
    //                        / |    | / |   <== Edges overlap in x direction
    //                       /  |    |/  |
    // TopContour  head>-->--->--->---->-->tail
    // Start at Edges:
    Edge *thisEdge = head->getBackEdge();
    Edge *thatEdge = bottomContour->getTail()->getFrontEdge();
    // Find the first thisEdge and thatEdge that overlap with each other.
    bool isThisContourMoreFront = false;
    if (isX1Smaller(getEdgeXStart(thisEdge), bottomContour->getEdgeXEnd(thatEdge))) {
        isThisContourMoreFront = true;
    }
    while (true) {
        if (thisEdge == tail || thatEdge == bottomContour->getHead()) {
            return;
        }
        if (isX1Larger(getEdgeXEnd(thisEdge), bottomContour->getEdgeXEnd(thatEdge)) &&
            isX1Smaller(getEdgeXStart(thisEdge), bottomContour->getEdgeXStart(thatEdge))) {
            break;
        } else if (isThisContourMoreFront) {
            thisEdge = thisEdge->getBackEdge();
        } else {
            thatEdge = thatEdge->getFrontEdge();
        }
    }
    // Legalize thisEdge.
    while (true) {
        if (thisEdge == tail || thatEdge == bottomContour->getHead()) {
            return;
        }
        int yDifference = getYDifference(getEdgeYEnd(thisEdge), bottomContour->getEdgeYEnd(thatEdge));
        if (yDifference > 0) {
            int newThisEdgeY = bottomContour->getEdgeYEnd(thatEdge);
            setEdgeYEnd(thisEdge, newThisEdgeY);
            MacroNode *macroNode = thisEdge->getMacroNode();
            Macro *macro = macroNode->getMacro();
            setMacroYEnd(macro, newThisEdgeY);
            macroNode->addToVerticalDisplacement(yDifference); // The sign of yDifference is for interiorContours.
            Edge *macroNodeBottomEdge = getMacroNodeBottomEdge(macroNode);
            if (macroNodeBottomEdge != 0) {
                setEdgeYStart(macroNodeBottomEdge, getMacroYStart(macro)); // bottomContour.setEdgeYEnd for bottomEdge. (Though strange usage)
            }
        }
        // Choose next Edges.
        int thisEdgeXEnd = getEdgeXEnd(thisEdge);
        int thatEdgeXStart = bottomContour->getEdgeXStart(thatEdge);
        if (isX1Larger(thisEdgeXEnd, thatEdgeXStart)) {
            thatEdge = thatEdge->getFrontEdge();
        } else if (isX1Smaller(thisEdgeXEnd, thatEdgeXStart)) {
            thisEdge = thisEdge->getBackEdge();
        } else {
            thatEdge = thatEdge->getFrontEdge();
            thisEdge = thisEdge->getBackEdge();
        }
    }
}

void Contour::legalizeMacrosToARightContour(Contour *rightContour) {
    // RightContour            head |
    //                        +-----v
    //                        |
    //                        +---+
    //                            |
    //                     +------y  <== yStart of the current Edge
    //                     |             with the largest x
    //                 +---+
    //            tail |
    //                 v
    // TopContour        head>--->----->------>tail
    // Start at Edges:
    Edge *thisEdge = head->getBackEdge();
    Edge *thatEdge = rightContour->getTail()->getFrontEdge();
    if (thisEdge == tail) {
        return;
    }
    // Find the first thatEdge whose xEnd is larger than thisEdge.xStart.
    while (true) {
        if (thatEdge == rightContour->getHead()) {
            return;
        }
        if (isX1Larger(rightContour->getEdgeYEnd(thatEdge), getEdgeXStart(thisEdge))) {
            break;
        } else {
            thatEdge = thatEdge->getFrontEdge();
        }
    }
    // Legalize thisEdge.
    while (true) {
        if (thisEdge == tail || thatEdge == rightContour->getHead()) {
            return;
        }
        int yDifference = getYDifference(getEdgeYEnd(thisEdge), rightContour->getEdgeXEnd(thatEdge));
        if (yDifference > 0) {
            int newThisEdgeY = rightContour->getEdgeXEnd(thatEdge);
            setEdgeYEnd(thisEdge, newThisEdgeY);
            MacroNode *macroNode = thisEdge->getMacroNode();
            Macro *macro = macroNode->getMacro();
            setMacroYEnd(macro, newThisEdgeY);
            macroNode->addToVerticalDisplacement(yDifference); // The sign of yDifference is for interiorContours.
            Edge *macroNodeBottomEdge = getMacroNodeBottomEdge(macroNode);
            if (macroNodeBottomEdge != 0) {
                setEdgeYStart(macroNodeBottomEdge, getMacroYStart(macro)); // Set bottomEdge's yEnd
            }
        }
        // Choose next thisEdge (and thatEdge).
        thisEdge = thisEdge->getBackEdge();
        if (isX1Larger(getEdgeXStart(thisEdge), rightContour->getEdgeYEnd(thatEdge))) {
            // Find thatEdge whose xEnd is larger than thisEdge.xStart.
            thatEdge = thatEdge->getFrontEdge();
            while (true) {
                if (thatEdge == rightContour->getHead()) {
                    return;
                }
                if (isX1Larger(rightContour->getEdgeYEnd(thatEdge), getEdgeXStart(thisEdge))) {
                    break;
                } else {
                    thatEdge = thatEdge->getFrontEdge();
                }
            }
        }
    }
}

void Contour::legalizeMacrosToALeftContour(Contour *leftContour) {
    // LeftContour                  | tail
    //                              ^-----+
    //                                    |
    //                                +---+
    //                                |
    //  yStart of the current Edge => y------+ 
    //  with the largest x                   |
    //                                       +---+
    //                                           | head
    //                                           ^
    // TopContour        head>--->----->------>tail
    // Start at Edges:
    Edge *thisEdge = tail->getFrontEdge();
    Edge *thatEdge = leftContour->getHead()->getBackEdge();
    if (thisEdge == head) {
        return;
    }
    // Find the first thatEdge whose xStart is smaller than thisEdge.xEnd.
    while (true) {
        if (thatEdge == leftContour->getTail()) {
            return;
        }
        if (isX1Smaller(leftContour->getEdgeYEnd(thatEdge), getEdgeXEnd(thisEdge))) {
            break;
        } else {
            thatEdge = thatEdge->getBackEdge();
        }
    }
    // Legalize thisEdge.
    while (true) {
        if (thisEdge == head || thatEdge == leftContour->getTail()) {
            return;
        }
        int yDifference = getYDifference(getEdgeYEnd(thisEdge), leftContour->getEdgeXStart(thatEdge));
        if (yDifference > 0) {
            int newThisEdgeY = leftContour->getEdgeXStart(thatEdge);
            setEdgeYEnd(thisEdge, newThisEdgeY);
            MacroNode *macroNode = thisEdge->getMacroNode();
            Macro *macro = macroNode->getMacro();
            setMacroYEnd(macro, newThisEdgeY);
            macroNode->addToVerticalDisplacement(yDifference); // The sign of yDifference is for interiorContours.
            Edge *macroNodeBottomEdge = getMacroNodeBottomEdge(macroNode);
            if (macroNodeBottomEdge != 0) {
                setEdgeYStart(macroNodeBottomEdge, getMacroYStart(macro)); // Set bottomEdge's yEnd
            }
        }
        // Choose next thisEdge (and thatEdge).
        thisEdge = thisEdge->getFrontEdge();
        if (isX1Smaller(getEdgeXEnd(thisEdge), leftContour->getEdgeYEnd(thatEdge))) {
            // Find thatEdge whose xStart is smaller than thisEdge.xEnd.
            thatEdge = thatEdge->getFrontEdge();
            while (true) {
                if (thatEdge == leftContour->getTail()) {
                    return;
                }
                if (isX1Smaller(leftContour->getEdgeYEnd(thatEdge), getEdgeXEnd(thisEdge))) {
                    break;
                } else {
                    thatEdge = thatEdge->getBackEdge();
                }
            }
        }
    }
}

void Contour::placeMacroOnTopOfMacroWithPackingForward(MacroNode *macroNode, MacroNode *onMacroNode) {
    Edge *onEdge = getMacroNodeTopEdge(onMacroNode);
    placeMacroOnEdgeWithPackingForward(macroNode, onEdge);
}

void Contour::placeMacroOnTopOfMacroWithPackingBackward(MacroNode *macroNode, MacroNode *onMacroNode) {
    Edge *onEdge = getMacroNodeTopEdge(onMacroNode);
    placeMacroOnEdgeWithPackingBackward(macroNode, onEdge);
}

void Contour::placeMacroOnEdgeWithPackingForward(MacroNode *macroNode, Edge *onEdge) {
    // Set Macro.xStart.
    Macro *macro = macroNode->getMacro();
    setMacroXStart(macro, getEdgeXStart(onEdge));
    Edge *insertedEdge = createMacroNodeTopEdge(macroNode);
    // Find Edges which need to be modified.
    initializeLocalMaxY();
    Edge *currentEdge = onEdge;
    std::vector<Edge *> *edgesToBeRemoved = new std::vector<Edge *>();
    while (true) {
        if (isX1NotLarger(getEdgeXEnd(currentEdge), getEdgeXEnd(insertedEdge))) {
            edgesToBeRemoved->push_back(currentEdge);
            updateLocalMaxY(getEdgeYEnd(currentEdge));
            currentEdge = currentEdge->getBackEdge();
        } else if (isX1Smaller(getEdgeXStart(currentEdge), getEdgeXEnd(insertedEdge))) {
            updateLocalMaxY(getEdgeYEnd(currentEdge));
            setEdgeXStart(currentEdge, getEdgeXEnd(insertedEdge));
            break;
        } else {
            break;
        }
    }
    // Insert
    setMacroYStart(macro, localMaxY);
    addToLocalMaxY(getMacroHeight(macro));
    setEdgeYEnd(insertedEdge, localMaxY);
    insertEdge(insertedEdge, onEdge->getFrontEdge());
    // Remove (after insertion)
    for (int i = 0; i < edgesToBeRemoved->size(); i++) {
        Edge *edgeToBeRemoved = edgesToBeRemoved->at(i);
        removeEdge(edgeToBeRemoved);
        // The Edge's MacroNode is now totally covered.
        MacroNode *edgeMacroNode = edgeToBeRemoved->getMacroNode();
        if (edgeMacroNode != 0) {
            edgeMacroNode->setCovered();
        }
    }
    delete edgesToBeRemoved;
    // Update the boundaries of the Contour.
    updateMaxY(localMaxY);
    updateMinY(getMacroYStart(macro));
    updateMaxX(getEdgeXEnd(insertedEdge));
    updateMinX(getEdgeXStart(insertedEdge));
}

void Contour::placeMacroOnEdgeWithPackingBackward(MacroNode *macroNode, Edge *onEdge) {
    // Set Macro.xEnd.
    Macro *macro = macroNode->getMacro();
    setMacroXEnd(macro, getEdgeXEnd(onEdge));
    Edge *insertedEdge = createMacroNodeTopEdge(macroNode);
    // Find Edges which need to be modified.
    initializeLocalMaxY();
    Edge *currentEdge = onEdge;
    std::vector<Edge *> *edgesToBeRemoved = new std::vector<Edge *>();
    while (true) {
        if (isX1NotSmaller(getEdgeXStart(currentEdge), getEdgeXStart(insertedEdge))) {
            edgesToBeRemoved->push_back(currentEdge);
            updateLocalMaxY(getEdgeYEnd(currentEdge));
            currentEdge = currentEdge->getFrontEdge();
        } else if (isX1Larger(getEdgeXEnd(currentEdge), getEdgeXStart(insertedEdge))) {
            updateLocalMaxY(getEdgeYEnd(currentEdge));
            setEdgeXEnd(currentEdge, getEdgeXStart(insertedEdge));
            break;
        } else {
            break;
        }
    }
    // Insert
    setMacroYStart(macro, localMaxY);
    addToLocalMaxY(getMacroHeight(macro));
    setEdgeYEnd(insertedEdge, localMaxY);
    insertEdgeAtFront(insertedEdge, onEdge->getBackEdge());   // insert at front of position
    // Remove (after insertion)
    for (int i = 0; i < edgesToBeRemoved->size(); i++) {
        Edge *edgeToBeRemoved = edgesToBeRemoved->at(i);
        removeEdge(edgeToBeRemoved);
        // The Edge's MacroNode is now totally covered.
        MacroNode *edgeMacroNode = edgeToBeRemoved->getMacroNode();
        if (edgeMacroNode != 0) {
            edgeMacroNode->setCovered();
        }
    }
    delete edgesToBeRemoved;
    // Update the boundaries of the Contour.
    updateMaxY(localMaxY);
    updateMinY(getMacroYStart(macro));
    updateMaxX(getEdgeXEnd(insertedEdge));
    updateMinX(getEdgeXStart(insertedEdge));
}

void Contour::placeMacroAtXWithPackingForward(MacroNode *macroNode, int x) {
    // From head, find the first Edge that its xEnd > x.
    Macro *macro = macroNode->getMacro();
    int insertedEdgeXEnd = addToX(x, getMacroWidth(macro));
    Edge *currentEdge = head;
    if (isX1NotLarger(insertedEdgeXEnd, getEdgeXStart(head)) ||
        isX1NotSmaller(x, getEdgeXEnd(tail))) {
        return;
    }
    while (true) {
        if (isX1Larger(getEdgeXEnd(currentEdge), x)) {
            break;
        }
        currentEdge = currentEdge->getBackEdge();
    }
    // If currentEdge.xStart < x, split currentEdge at x by
    //     1. creating a new Edge and insert it to the Contour,
    //        while new Edge's macroNode remains zero;
    //     2. setting currentEdge.xEnd to x.
    // Then set the new Edge as currentEdge.
    //
    //             +-----+                         +-----+
    //     Macro   |  m  |                         |  m  |
    //             +-----+     split the Edge      +-----+
    //              e               ==>          e   e2
    //   Edge  >-------->                      >--->---->
    if (isX1Smaller(getEdgeXStart(currentEdge), x)) {
        Edge *newEdge = createTopEdge(x, getEdgeXEnd(currentEdge), getEdgeYEnd(currentEdge));
        insertEdge(newEdge, currentEdge);
        setEdgeXEnd(currentEdge, x);
        currentEdge = newEdge;
    }
    // Now currentEdge.xStart == x. (It is impossible that xStart > x.)
    // Use placeMacroOnEdgeWithPackingForward() to place the Macro.
    placeMacroOnEdgeWithPackingForward(macroNode, currentEdge);
}

void Contour::placeMacroAtXWithPackingBackward(MacroNode *macroNode, int x) {
    // From tail, find the first Edge that its xStart < x.
    Macro *macro = macroNode->getMacro();
    int insertedEdgeXStart = addToX(x, getMacroWidth(macro) * -1);
    Edge *currentEdge = tail;
    if (isX1NotSmaller(insertedEdgeXStart, getEdgeXEnd(tail)) ||
        isX1NotLarger(x, getEdgeXStart(head))) {
        return;
    }
    while (true) {
        if (isX1Smaller(getEdgeXStart(currentEdge), x)) {
            break;
        }
        currentEdge = currentEdge->getFrontEdge();
    }
    // If currentEdge.xEnd > x, split currentEdge at x by
    //     1. creating a new Edge and insert it to the Contour,
    //        while new Edge's macroNode remains zero;
    //     2. setting currentEdge.xStart to x.
    // Then set the new Edge as currentEdge.
    //
    //          +-----+                         +-----+
    //  Macro   |  m  |                         |  m  |
    //          +-----+      split the Edge     +-----+
    //                e            ==>             e2   e
    //   Edge    >-------->                      >---->--->
    if (isX1Larger(getEdgeXEnd(currentEdge), x)) {
        Edge *newEdge = createTopEdge(getEdgeXStart(currentEdge), x, getEdgeYEnd(currentEdge));
        insertEdge(newEdge, currentEdge->getFrontEdge());
        setEdgeXStart(currentEdge, x);
        currentEdge = newEdge;
    }
    // Now currentEdge.xEnd == x. (It is impossible that xEnd < x.)
    // Use placeMacroOnEdgeWithPackingForward() to place the Macro.
    placeMacroOnEdgeWithPackingBackward(macroNode, currentEdge);
}

void Contour::printEdges() {
    Edge *current = head;
    while (true) {
        std::cout << "(" << getEdgeXStart(current) << ",\t"
                         << getEdgeXEnd(current) << ",\t"
                         << getEdgeYEnd(current) << ")\n";
        if (current != tail) {
            current = current->getBackEdge();
        } else {
            break;
        }
    }
}

void Contour::updateLocalMaxY(int y) {
    if (isY1Larger(y, localMaxY))
        localMaxY = y;
}

void Contour::updateMaxX(int x) {
    if (isX1Larger(x, maxX))
        maxX = x;
}

void Contour::updateMinX(int x) {
    if (isX1Smaller(x, minX))
        minX = x;
}

void Contour::updateMaxY(int y) {
    if (isY1Larger(y, maxY))
        maxY = y;
}

void Contour::updateMinY(int y) {
    if (isY1Smaller(y, maxY))
        maxY = y;
}
