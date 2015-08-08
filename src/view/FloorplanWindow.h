#ifndef VIEW_FLOORPLANWINDOW_H_
#define VIEW_FLOORPLANWINDOW_H_

#include "view/Window.h"

class Floorplan;
class FloorplanView;

class FloorplanWindow : public Window {
public:
    // Singleton
    static FloorplanWindow *floorplanWindow;
    static FloorplanWindow *createInstance(Floorplan *floorplan);
    static FloorplanWindow *getInstance();

    /*
    Delete floorplanView.
    */
    ~FloorplanWindow();
    void setXYRangeByFloorplan();
    /*
    @Override
    */
    void display();
    /*
    @Override
    */
    void setDisplayFunction();
    
private:
    // Singleton
    FloorplanWindow(Floorplan *floorplan);

    Floorplan *floorplan;
    FloorplanView *floorplanView;
};

#endif