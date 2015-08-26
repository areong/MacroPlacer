#include "sa/DecreaseVariable.h"
#include "sa/Variable.h"

DecreaseVariable::DecreaseVariable(double decrement) {
    this->decrement = decrement;
}

DecreaseVariable::~DecreaseVariable() {

}

void DecreaseVariable::operate(State *state) {
    Variable *variable = dynamic_cast<Variable *>(state);
    variable->setValue(variable->getValue() - decrement);
}
