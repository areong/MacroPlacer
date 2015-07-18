#ifndef MODEL_MACRO_H_
#define MODEL_MACRO_H_

/*
Not complete.
*/
class Macro {
public:
    Macro();
    Macro(int width, int height);
    ~Macro();
    int getWidth();
    int getHeight();
    void setXStart(int xStart);
    int getXStart();
    void setXEnd(int xEnd);
    int getXEnd();
    void setYStart(int yStart);
    int getYStart();
    void setYEnd(int yEnd);
    int getYEnd();
    Macro *copy();

private:
    int width;
    int height;
    int xStart;
    int xEnd;
    int yStart;
    int yEnd;
};

#endif