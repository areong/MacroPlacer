#ifndef SA_DECREASEVARIABLE_H_
#define SA_DECREASEVARIABLE_H_

#include "sa/Operation.h"

/*
The class is for testing sa/.
It only takes Variable as State.
*/
class DecreaseVariable : public Operation {
public:
    DecreaseVariable(double decrement);
    ~DecreaseVariable();
    /*
    @Override
    @param state A Variable.
    */
    void operate(State *state);

private:
    double decrement;
};

#endif