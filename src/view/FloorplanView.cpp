#include "view/FloorplanView.h"
#include "model/Floorplan.h"
#include "tree/icptree/ICPTree.h"
#include "tree/icptree/MacroNode.h"
#include "view/MacroView.h"
#include "view/Window.h"

FloorplanView::FloorplanView(Window *window, Floorplan *floorplan) : View(window) {
    this->floorplan = floorplan;
    macroViews = new std::vector<MacroView *>();
    std::vector<Macro *> *macros = floorplan->getMacros();
    for (int i = 0; i < macros->size(); i++) {
        macroViews->push_back(new MacroView(window, macros->at(i)));
    }
}

FloorplanView::~FloorplanView() {
    for (int i = 0; i < macroViews->size(); i++) {
        delete macroViews->at(i);
    }
    delete macroViews;
}

void FloorplanView::display() {
    // Bounding box
    window->drawRectangle(floorplan->getMinX(), floorplan->getMaxX(),
        floorplan->getMinY(), floorplan->getMaxY(),
        0, 0, 0, 0.6, 0.6, 0.6);
    // Empty Macros
    std::vector<MacroNode *> *emptyMacroNodes = floorplan->getICPTree()->getEmptyNodes();
    for (int i = 0; i < emptyMacroNodes->size(); i++) {
        MacroView *emptyMacroView = new MacroView(window, emptyMacroNodes->at(i)->getMacro());
        emptyMacroView->setFillColor(0, 0.1, 0.1);
        emptyMacroView->setOutlineColor(0.4, 0.5, 0.5);
        emptyMacroView->display();
        delete emptyMacroView;
    }
    delete emptyMacroNodes;
    // Macros
    for (int i = 0; i < macroViews->size(); i++) {
        MacroView *macroView = macroViews->at(i);
        // Determine color.
        switch (floorplan->getMacroNodes()->at(i)->getIdentity()) {
        case MacroNode::NORMAL_NODE:
            macroView->setFillColor(0.2, 0.4, 0.5);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        case MacroNode::BRANCH_NODE:
            macroView->setFillColor(0.5, 0.6, 0.1);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        case MacroNode::SWITCH_NODE:
            macroView->setFillColor(0.1, 0.8, 0.0);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        case MacroNode::CORNER_NODE:
            macroView->setFillColor(0.8, 0.2, 0.1);
            macroView->setOutlineColor(1, 0.9, 0.9);
            break;
        default:
            macroView->setFillColor(0.2, 0.4, 0.5);
            macroView->setOutlineColor(1, 0.9, 0.9);
        }
        macroView->display();
    }
}
