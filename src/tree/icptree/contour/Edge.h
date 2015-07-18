#ifndef TREE_ICPTREE_CONTOUR_EDGE_H_
#define TREE_ICPTREE_CONTOUR_EDGE_H_

class MacroNode;

class Edge {
public:
    Edge();
    ~Edge();
    void setXStart(int xStart);
    int getXStart();
    void setXEnd(int xEnd);
    int getXEnd();
    void setYStart(int yStart);
    int getYStart();
    void setYEnd(int yEnd);
    int getYEnd();
    void setMacroNode(MacroNode *macroNode);
    MacroNode *getMacroNode();

    // For Contour, a doubly-linked list
    
    void setFrontEdge(Edge *edge);
    Edge *getFrontEdge();
    void setBackEdge(Edge *edge);
    Edge *getBackEdge();

    static Edge *createTopEdge(int xStart, int xEnd, int y);
    static Edge *createRightEdge(int yEnd, int yStart, int x);
    static Edge *createBottomEdge(int xEnd, int xStart, int y);
    static Edge *createLeftEdge(int yStart, int yEnd, int x);

private:
    int xStart;
    int xEnd;
    int yStart;
    int yEnd;
    MacroNode *macroNode;   // Set it covered when the Edge is removed from Contour.
    
    // For Contour, a doubly-linked list

    Edge *frontEdge;
    Edge *backEdge;
};

#endif