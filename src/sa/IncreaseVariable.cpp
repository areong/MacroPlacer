#include "sa/IncreaseVariable.h"
#include "sa/Variable.h"

IncreaseVariable::IncreaseVariable(double increment) {
    this->increment = increment;
}

IncreaseVariable::~IncreaseVariable() {

}

void IncreaseVariable::operate(State *state) {
    Variable *variable = dynamic_cast<Variable *>(state);
    variable->setValue(variable->getValue() + increment);
}
