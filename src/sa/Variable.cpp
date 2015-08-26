#include "sa/Variable.h"

Variable::Variable(double x) {
    this->x = x;
}

Variable::~Variable() {

}

void Variable::setValue(double x) {
    this->x = x;
}

double Variable::getValue() {
    return x;
}

State *Variable::copy() {
    return new Variable(x);
}
