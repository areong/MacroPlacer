#ifndef TREE_ICPTREE_CONTOUR_BOTTOMCONTOUR_H_
#define TREE_ICPTREE_CONTOUR_BOTTOMCONTOUR_H_

#include "tree/icptree/contour/Contour.h"

class BottomContour : public Contour {
public:
    BottomContour();
    ~BottomContour();
    /*
    @Override
    */
    void initializeHeadAndTail(int originX, int originY);
    /*
    @Override
    */
    int getOriginX();
    /*
    @Override
    */
    int getOriginY();
    /*
    @Override
    */
    void setMacroXStart(Macro *macro, int xStart);
    /*
    @Override
    */
    void setMacroXEnd(Macro *macro, int xEnd);
    /*
    @Override
    */
    void setMacroYStart(Macro *macro, int yStart);
    /*
    @Override
    */
    void setMacroYEnd(Macro *macro, int yEnd);
    /*
    @Override
    */
    int getMacroXStart(Macro *macro);
    /*
    @Override
    */
    int getMacroXEnd(Macro *macro);
    /*
    @Override
    */
    int getMacroYStart(Macro *macro);
    /*
    @Override
    */
    int getMacroYEnd(Macro *macro);
    /*
    @Override
    */
    int getMacroWidth(Macro *macro);
    /*
    @Override
    */
    int getMacroHeight(Macro *macro);
    /*
    @Override
    */
    Edge *createTopEdge(int xStart, int xEnd, int y);
    /*
    @Override
    */
    Edge *createMacroNodeTopEdge(MacroNode *macroNode);
    /*
    @Override
    */
    Edge *getMacroNodeTopEdge(MacroNode *macroNode);
    /*
    @Override
    */
    Edge *getMacroNodeBottomEdge(MacroNode *macroNode);
    /*
    @Override
    */
    void setEdgeXStart(Edge *edge, int xStart);
    /*
    @Override
    */
    void setEdgeXEnd(Edge *edge, int xEnd);
    /*
    @Override
    */
    void setEdgeYStart(Edge *edge, int yStart);
    /*
    @Override
    */
    void setEdgeYEnd(Edge *edge, int yEnd);
    /*
    @Override
    */
    int getEdgeXStart(Edge *edge);
    /*
    @Override
    */
    int getEdgeXEnd(Edge *edge);
    /*
    @Override
    */
    int getEdgeYStart(Edge *edge);
    /*
    @Override
    */
    int getEdgeYEnd(Edge *edge);
    /*
    @Override
    */
    void initializeLocalMaxY();
    /*
    @Override
    */
    void addToLocalMaxY(int value);
    /*
    @Override
    */
    void initializeMaxMinXY();
    /*
    @Override
    */
    bool isX1Larger(int x1, int x2);
    /*
    @Override
    */
    bool isX1NotSmaller(int x1, int x2);
    /*
    @Override
    */
    bool isX1Smaller(int x1, int x2);
    /*
    @Override
    */
    bool isX1NotLarger(int x1, int x2);
    /*
    @Override
    */
    bool isY1Larger(int y1, int y2);
    /*
    @Override
    */
    bool isY1NotSmaller(int y1, int y2);
    /*
    @Override
    */
    bool isY1Smaller(int y1, int y2);
    /*
    @Override
    */
    bool isY1NotLarger(int y1, int y2);
    /*
    @Override
    */
    int getYDifference(int y1, int y2);
    /*
    @Override
    */
    int addToX(int x, int value);
    /*
    @Override
    */
    int addToY(int y, int value);
};

#endif