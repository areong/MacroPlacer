#ifndef SA_OPERATIONSET_H_
#define SA_OPERATIONSET_H_

#include "sa/Operation.h"
#include <vector>

class OperationSet : public Operation {
public:
    OperationSet();
    /*
    Delete the vector but not each Operation to avoid double deletion.
    */
    ~OperationSet();
    void addOperation(Operation *operation);
    /*
    @Override
    Randomly choose an Operation and operate the State.
    The probability of choosing each Operation is the same.
    */
    void operate(State *state);

private:
    std::vector<Operation *> *operations;
};

#endif