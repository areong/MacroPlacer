#ifndef MODEL_MODULE_H_
#define MODEL_MODULE_H_

#include <string>
#include <vector>

class Pin;

/*
The base class of Macro, Cell and Terminal.
This class is responsible for common behaviors related to Pin.
*/
class Module {
public:
    Module(std::string name);
    /*
    Delete all Pins.
    */
    ~Module();
    std::string getName();
    /*
    Add Pin and call Pin.setModule(this).
    */
    void addPin(Pin *pin);
    /*
    Get the Pin by linear search.
    @return If no Pin matches, return 0.
    */
    Pin *getPinByOffset(double offsetX, double offsetY);
    /*
    Return the x component of the origin of the Pins' offsets.
    */
    virtual double getPinsOriginX() = 0;
    /*
    Return the y component of the origin of the Pins' offsets.
    */
    virtual double getPinsOriginY() = 0;
    void updatePinsPosition();
    /*
    Update the attribute rotation.
    Please call this method first in Subclass.rotate() if
    the subclasses override this method.
    */
    virtual void rotate(bool counterclockwise);
    /*
    @return 0, 1, 2, 3 for 0, 90, 180, 270 degrees rotation.
    */
    int getRotation();

protected:
    /*
    Record the rotation of the Module.
    Though it is a protected attribute, it is recommended not to modify
    it directly in subclasses. Use Module.rotate() instead.
    */
    int rotation;
    /*
    Though it is a protected attribute, it is recommended not to modify
    it directly in subclasses. Use Module.addPin() instead.
    */
    std::vector<Pin *> *pins;

private:
    /*
    0, 1, 2, 3 for 0, 90, 180, 270 degrees rotation.
    */
    std::string name;
};

#endif