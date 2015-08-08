#include "view/MacroView.h"
#include "model/Macro.h"
#include "view/Window.h"

MacroView::MacroView(Window *window, Macro *macro) : View(window) {
    this->macro = macro;
    fillColor[0] = 0.2;
    fillColor[1] = 0.4;
    fillColor[2] = 0.5;
    outlineColor[0] = 1;
    outlineColor[1] = 0.9;
    outlineColor[2] = 0.9;
}

MacroView::~MacroView() {

}

void MacroView::setFillColor(float r, float g, float b) {
    fillColor[0] = r;
    fillColor[1] = g;
    fillColor[2] = b;
}

void MacroView::setOutlineColor(float r, float g, float b) {
    outlineColor[0] = r;
    outlineColor[1] = g;
    outlineColor[2] = b;
}

void MacroView::display() {
    window->drawRectangle(macro->getXStart(), macro->getXEnd(),
        macro->getYStart(), macro->getYEnd(),
        fillColor[0], fillColor[1], fillColor[2],
        outlineColor[0], outlineColor[1], outlineColor[2]);
}
