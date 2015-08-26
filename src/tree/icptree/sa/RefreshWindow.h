#ifndef TREE_ICPTREE_SA_REFRESHWINDOW_H_
#define TREE_ICPTREE_SA_REFRESHWINDOW_H_

#include "sa/TemperatureListener.h"

class Floorplan;
class Window;

class RefreshWindow : public TemperatureListener {
public:
    RefreshWindow(Window *window, Floorplan *floorplan);
    ~RefreshWindow();
    /*
    @Override
    Place the best ICPTree, assign it to the Floorplan, and then refresh the Window.
    Thus the Window shows the current best ICPTree (the Window is assumed to be
    a FloorplanWindow).
    */
    void onUpdate();

private:
    Window *window;
    Floorplan *floorplan;
};

#endif