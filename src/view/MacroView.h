#ifndef VIEW_MACROVIEW_H_
#define VIEW_MACROVIEW_H_

#include "view/View.h"

class Macro;

class MacroView : public View {
public:
    MacroView(Window *window, Macro *macro);
    ~MacroView();
    void setFillColor(float r, float g, float b);
    void setOutlineColor(float r, float g, float b);
    /*
    @Override
    */
    void display();
    
private:
    Macro *macro;
    float fillColor[3];
    float outlineColor[3];
};

#endif