#ifndef SA_OPERATION_H_
#define SA_OPERATION_H_

class State;

class Operation {
public:
    virtual void operate(State *state) = 0;
};

#endif