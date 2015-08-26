#ifndef VIEW_FLOORPLANVIEW_H_
#define VIEW_FLOORPLANVIEW_H_

#include <vector>
#include "view/View.h"

class Floorplan;
class MacroView;

class FloorplanView : public View {
public:
    /*
    Create MacroViews for all Macros from the floorplan.
    */
    FloorplanView(Window *window, Floorplan *floorplan);
    /*
    Delete all MacroViews.
    */
    ~FloorplanView();
    /*
    @Override
    */
    void display();

private:
    Floorplan *floorplan;
    //std::vector<MacroView *> *macroViews;
};

#endif