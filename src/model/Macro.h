#ifndef MODEL_MACRO_H_
#define MODEL_MACRO_H_

#include "model/Module.h"

class Macro : public Module {
public:
    /*
    ASSUME width > 0.
    */
    Macro(int width=1, int height=1, std::string name="");
    ~Macro();
    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void calculateArea();
    int getArea();
    void calculateAspectRatio();
    double getAspectRatio();
    void setXStart(int xStart);
    int getXStart();
    void setXEnd(int xEnd);
    int getXEnd();
    void setYStart(int yStart);
    int getYStart();
    void setYEnd(int yEnd);
    int getYEnd();
    /*
    @Override
    */
    double getPinsOriginX();
    /*
    @Override
    */
    double getPinsOriginY();
    /*
    @Override
    Swap width and height.
    */
    void rotate(bool counterclockwise);
    double calculateAreaUnderRectangle(double xStart, double yStart, double xEnd, double yEnd);
    /*
    Does not copy pins because it is not necessary.
    */
    Macro *copy();

private:
    int width;
    int height;
    int area;
    double aspectRatio;
    int xStart;
    int xEnd;
    int yStart;
    int yEnd;
};

#endif