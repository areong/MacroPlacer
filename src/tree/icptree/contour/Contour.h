#ifndef TREE_ICPTREE_CONTOUR_CONTOUR_H_
#define TREE_ICPTREE_CONTOUR_CONTOUR_H_

#include <vector>

class Edge;
class Macro;
class MacroNode;

/*
DO NOT CREATE OBJECT OF THIS CLASS.
The methods are named as if the Contour is a TopContour.
All kinds of Contours override these methods to make them behave correctly.
*/
class Contour {
public:
    /*
    The constructor does nothing.

    DEVELOPMENT MEMO
    1.  To achieve polymorism among subclasses, first I called
        initializeHeadAndTail() and initializeMaxMinXY() in the constructor.
        However the compiler does no allow calling pure virtual functions
        inside the constructor.
    2.  I moved the whole code of constructor to initialize(), and call it
        in the constructor. In a subclass, the constructor has the same
        input arguments and calls the base class constructor like this:
            TopContour::TopContour(int originX, int originY)
                : Contour(originX, originY) {}
        I deceived the compiler, though, an error occured at running time
        saying that pure virtual functions were called.
    3.  To avoid calling pure virtual functions in Contour's constructor,
        I removed the constructor's input arguments and made the function
        body empty. Users now have to call Contour.initialize(int, int)
        after creating an object of a Contour's subclass.
    */
    Contour();
    /*
    Delete head and tail.
    Do not delete the other Edges, which are created by MacroNodes and
    will be deleted by the MacroNodes.
    */
    virtual ~Contour();
    /*
    MUST CALL THIS METHOD
    Call this method right after constructor to create head and tail.
    @param originX The x where head ends and tail starts (for TopContour).
    @param originY The y of head and tail (for TopContour).
    */
    void initialize(int originX, int originY);
    Edge *getHead();
    Edge *getTail();
    /*
    Insert edge at the back of position.
    */
    void insertEdge(Edge *edge, Edge *position);
    /*
    Insert edge at the front of position. It is used in packing backward.
    */
    void insertEdgeAtFront(Edge *edge, Edge *position);
    /*
    It is assumed that edge is between head and tail, and
    the frontEdge and backEdge of the edge exist.
    */
    void removeEdge(Edge *edge);
    /*
    Place the Macro on Contour.tail with packing forward.
    Macro.yStart will be set by MacroNode.verticalDisplacement.
    Assume Macro.width is smaller than tail's length.
    Used in updating exterior contours when placing Macros on branches in ICPTree.
    */
    void placeMacroOnTailByVerticalDisplacementWithPackingForward(MacroNode *macroNode);
    /*
    Place the Macro on Contour.head with packing backward.
    Macro.yStart will not be changed.
    Assume Macro.width is smaller than head's length.
    Used in updating interior contours when placing Macros on branches in ICPTree.
    */
    void placeMacroOnHeadWithoutChangingMacroYStartWithPackingBackward(MacroNode *macroNode);
    /*
    Set Contour.tail.yEnd to Contour.tail.frontEdge.macroNode.macro.yStart.
    Used in adjusting exterior contours after placing Macros of one branch in ICPTree.
    */
    void setTailYToTheLastMacroYStart();
    /*
    Set the Macros' yEnd such that for all Macro pairs, (m1, m2),
    where m1 is from this TopContour, m2 is from the BottomContour
    and m1 overlaps with m2 in x direction,
    m1.yEnd <= m2.yStart (get from getMacroYEnd()).
    Also set MacroNode.verticalDisplacement.
    A Macro is from a Contour iff its Edge is in the Contour.
    Used for legalizing interior Contours.
    */
    void legalizeMacrosToABottomContour(Contour *bottomContour);
    /*
    Set the Macros' yEnd such that for all Macro pairs, (m1, m2),
    where m1 is from this TopContour, m2 is from the RightContour
    and m1.xStart < m2.xEnd,
    m1.yEnd <= m2.yStart (get from getMacroXEnd()).
    Also set MacroNode.verticalDisplacement.
    A Macro is from a Contour iff its Edge is in the Contour.
    Used for legalizing interior Contours.
    */
    void legalizeMacrosToARightContour(Contour *rightContour);
    /*
    Set the Macros' yEnd such that for all Macro pairs, (m1, m2),
    where m1 is from this TopContour, m2 is from the LeftContour
    and m1.xEnd > m2.xStart,
    m1.yEnd <= m2.yStart (get from getMacroXStart()).
    Also set MacroNode.verticalDisplacement.
    A Macro is from a Contour iff its Edge is in the Contour.
    Used for legalizing interior Contours.
    */
    void legalizeMacrosToALeftContour(Contour *leftContour);
    /*
    Place Macro on another Macro.
    Assume the second Macro's MacroNode, onMacroNode, is already placed
    on the Contour, thus its topEdge exists.
    */
    void placeMacroOnTopOfMacroWithPackingForward(MacroNode *macroNode, MacroNode *onMacroNode);
    void placeMacroOnTopOfMacroWithPackingBackward(MacroNode *macroNode, MacroNode *onMacroNode);
    /*
    @param macroNode The MacroNode whose Macro is to be placed.
    @param onEdge An Edge in the Contour.
    */
    void placeMacroOnEdgeWithPackingForward(MacroNode *macroNode, Edge *onEdge);
    void placeMacroOnEdgeWithPackingBackward(MacroNode *macroNode, Edge *onEdge);
    /*
    @param macroNode The MacroNode whose Macro is to be placed.
    @param x Macro.xStart will be set to x. If x + width <= head.xStart
             or x >= tail.xEnd, do not place.
    */
    void placeMacroAtXWithPackingForward(MacroNode *macroNode, int x);
    void placeMacroAtXWithPackingBackward(MacroNode *macroNode, int x);
    /*
    Calculate maxY by traversing all Edges.
    "All Edges" excludes head and tail.
    */
    void calculateMaxY();
    int getMaxX();
    int getMinX();
    int getMaxY();
    int getMinY();
    /*
    Print all Edges into lines of "(xStart, xEnd, y)"
    by calling Contour.getEdgeXStart(), getEdgeXEnd() and getEdgeY().
    */
    void printEdges();
    /*
    Create new Edges and assign them to head and tail, which are
    protected attributes.
    */
    virtual void initializeHeadAndTail(int originX, int originY) = 0;
    virtual int getOriginX() = 0;
    virtual int getOriginY() = 0;
    virtual void setMacroXStart(Macro *macro, int xStart) = 0;
    virtual void setMacroXEnd(Macro *macro, int xEnd) = 0;
    virtual void setMacroYStart(Macro *macro, int yStart) = 0;
    virtual void setMacroYEnd(Macro *macro, int yEnd) = 0;
    virtual int getMacroXStart(Macro *macro) = 0;
    virtual int getMacroXEnd(Macro *macro) = 0;
    virtual int getMacroYStart(Macro *macro) = 0;
    virtual int getMacroYEnd(Macro *macro) = 0;
    virtual int getMacroWidth(Macro *macro) = 0;
    virtual int getMacroHeight(Macro *macro) = 0;
    virtual void setMacroNodeMacroXStart(MacroNode *macroNode, int xStart) = 0;
    virtual void setMacroNodeMacroXEnd(MacroNode *macroNode, int xEnd) = 0;
    virtual void setMacroNodeMacroYStart(MacroNode *macroNode, int yStart) = 0;
    virtual void setMacroNodeMacroYEnd(MacroNode *macroNode, int yEnd) = 0;
    virtual Edge *createTopEdge(int xStart, int xEnd, int y) = 0;
    virtual Edge *createMacroNodeTopEdge(MacroNode *macroNode) = 0;
    virtual Edge *getMacroNodeTopEdge(MacroNode *macroNode) = 0;
    virtual Edge *getMacroNodeBottomEdge(MacroNode *macroNode) = 0;
    virtual void setEdgeXStart(Edge *edge, int xStart) = 0;
    virtual void setEdgeXEnd(Edge *edge, int xEnd) = 0;
    virtual void setEdgeYStart(Edge *edge, int yStart) = 0;
    virtual void setEdgeYEnd(Edge *edge, int yEnd) = 0;
    virtual int getEdgeXStart(Edge *edge) = 0;
    virtual int getEdgeXEnd(Edge *edge) = 0;
    virtual int getEdgeYStart(Edge *edge) = 0;
    virtual int getEdgeYEnd(Edge *edge) = 0;
    virtual void initializeLocalMaxY() = 0; // localMaxY is a protected attribute.
    virtual void addToLocalMaxY(int value) = 0;
    virtual void initializeMaxMinXY() = 0;  // min max x y are protected attributes.
    virtual void initializeMaxY() = 0;
    virtual bool isX1Larger(int x1, int x2) = 0;        // x1 >  x2
    virtual bool isX1NotSmaller(int x1, int x2) = 0;    // x1 >= x2
    virtual bool isX1Smaller(int x1, int x2) = 0;       // x1 <  x2
    virtual bool isX1NotLarger(int x1, int x2) = 0;     // x1 <= x2
    virtual bool isY1Larger(int y1, int y2) = 0;        // y1 >  y2
    virtual bool isY1NotSmaller(int y1, int y2) = 0;    // y1 >= y2
    virtual bool isY1Smaller(int y1, int y2) = 0;       // y1 <  y2
    virtual bool isY1NotLarger(int y1, int y2) = 0;     // y1 <= y2
    virtual int getYDifference(int y1, int y2) = 0;     // y1 - y2
    virtual int addToX(int x, int value) = 0;           // x + value
    virtual int addToY(int y, int value) = 0;           // y + value

protected:
    Edge *head;
    Edge *tail;
    int originX;
    int originY;
    int localMaxY;

    /*
    These four attributes are polymophised. For example, maxX
    represents max x, min y, min x and max y of TopContour,
    RightContour, BottomContour and LeftContour.
    */
    int maxX;
    int minX;
    int maxY;
    int minY;

private:
    // Collect edges in removeEdge() and ~Contour() for deletion.
    std::vector<Edge *> *edgesToBeDeleted;

    void updateLocalMaxY(int y);
    void updateMaxX(int x);
    void updateMinX(int x);
    void updateMaxY(int y);
    void updateMinY(int y);
};

#endif