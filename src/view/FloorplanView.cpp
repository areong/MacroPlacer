#include "view/FloorplanView.h"
#include "model/Bin.h"
#include "model/Floorplan.h"
#include "tree/icptree/ICPTree.h"
//#include "tree/icptree/MacroNode.h"
//#include "view/MacroView.h"
#include "view/TraversalTaskDrawMacroNode.h"
#include "view/Window.h"

FloorplanView::FloorplanView(Window *window, Floorplan *floorplan) : View(window) {
    this->floorplan = floorplan;
    //macroViews = new std::vector<MacroView *>();
    //std::vector<Macro *> *macros = floorplan->getMacros();
    //for (int i = 0; i < macros->size(); i++) {
    //    macroViews->push_back(new MacroView(window, macros->at(i)));
    //}
}

FloorplanView::~FloorplanView() {
    //for (int i = 0; i < macroViews->size(); i++) {
    //    delete macroViews->at(i);
    //}
    //delete macroViews;
}

void FloorplanView::display() {
    // Bins with Macros
    for (int i = 0; i < floorplan->getBinsRows()->size(); ++i) {
        for (int j = 0; j < floorplan->getBinsRows()->at(i)->size(); ++j) {
            Bin *bin = floorplan->getBinsRows()->at(i)->at(j);
            //if (bin->getPreplacedMacros()->empty() && bin->getMovableMacros()->empty()) {
            //    continue;
            //}
            //if (i >= 21 && i < 31 && j >= 21 && j < 31) {
            if (i >= 10 && i < 13 && j >= 10 && j < 13) {
            window->drawRectangle((float) bin->getXStart(), (float) bin->getXEnd(),
                (float) bin->getYStart(), (float) bin->getYEnd(),
                0.3, 0.1, 0, 0, 0, 0);        
            }
        }
    }
    // Bounding box
    window->drawRectangle(floorplan->getMinX(), floorplan->getMaxX(),
        floorplan->getMinY(), floorplan->getMaxY(),
        0, 0, 0, 0.6, 0.6, 0.6, true);
    TraversalTaskDrawMacroNode *task = new TraversalTaskDrawMacroNode(window);
    floorplan->getICPTree()->traverseAll(task);
    delete task;

    //// Empty Macros
    //std::vector<MacroNode *> *emptyMacroNodes = floorplan->getICPTree()->getEmptyNodes();
    //for (int i = 0; i < emptyMacroNodes->size(); i++) {
    //    MacroView *emptyMacroView = new MacroView(window, emptyMacroNodes->at(i)->getMacro());
    //    emptyMacroView->setFillColor(0, 0.1, 0.1);
    //    emptyMacroView->setOutlineColor(0.4, 0.5, 0.5);
    //    emptyMacroView->display();
    //    delete emptyMacroView;
    //}
    //delete emptyMacroNodes;
    //// Macros
    //for (int i = 0; i < macroViews->size(); i++) {
    //    MacroView *macroView = macroViews->at(i);
    //    // Determine color.
    //    switch (floorplan->getMacroNodes()->at(i)->getIdentity()) {
    //    case MacroNode::NORMAL_NODE:
    //        macroView->setFillColor(0.2, 0.4, 0.5);
    //        macroView->setOutlineColor(1, 0.9, 0.9);
    //        break;
    //    case MacroNode::BRANCH_NODE:
    //        macroView->setFillColor(0.5, 0.6, 0.1);
    //        macroView->setOutlineColor(1, 0.9, 0.9);
    //        break;
    //    case MacroNode::SWITCH_NODE:
    //        macroView->setFillColor(0.1, 0.8, 0.0);
    //        macroView->setOutlineColor(1, 0.9, 0.9);
    //        break;
    //    case MacroNode::CORNER_NODE:
    //        macroView->setFillColor(0.8, 0.2, 0.1);
    //        macroView->setOutlineColor(1, 0.9, 0.9);
    //        break;
    //    default:
    //        macroView->setFillColor(0.2, 0.4, 0.5);
    //        macroView->setOutlineColor(1, 0.9, 0.9);
    //    }
    //    macroView->display();
    //}
}
