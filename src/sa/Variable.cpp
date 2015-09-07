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

void Variable::doAfterBeingOperated() {

}

void Variable::doBeforeCalculatingCost() {

}

State *Variable::copy() {
    return new Variable(x);
}
