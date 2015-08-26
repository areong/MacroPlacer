#ifndef SA_INCREASEVARIABLE_H_
#define SA_INCREASEVARIABLE_H_

#include "sa/Operation.h"

/*
The class is for testing sa/.
It only takes Variable as State.
*/
class IncreaseVariable : public Operation {
public:
    IncreaseVariable(double increment);
    ~IncreaseVariable();
    /*
    @Override
    @param state A Variable.
    */
    void operate(State *state);

private:
    double increment;
};

#endif