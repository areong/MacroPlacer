#ifndef SA_VARIABLE_H_
#define SA_VARIABLE_H_

#include "sa/State.h"

/*
The class is for testing sa/.
*/
class Variable : public State {
public:
    Variable(double x = 0);
    ~Variable();
    void setValue(double x);
    double getValue();
    /*
    @Override
    */
    State *copy();

private:
    double x;
};

#endif