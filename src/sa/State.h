#ifndef SA_STATE_H_
#define SA_STATE_H_

class State {
public:
    virtual State *copy() = 0;
};

#endif