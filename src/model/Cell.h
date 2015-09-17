#ifndef MODEL_CELL_H_
#define MODEL_CELL_H_

#include "model/Module.h"

class Cell : public Module {
public:
    Cell(int width, int height, std::string name);
    ~Cell();
    int getWidth();
    int getHeight();
    /*
    @Override
    */
    double getPinsOriginX();
    /*
    @Override
    */
    double getPinsOriginY();
    
private:
    int width;
    int height;
};

#endif