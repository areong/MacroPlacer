#include "sa/Polynomial.h"
#include "sa/Variable.h"

Polynomial::Polynomial(double a4, double a3, double a2, double a1, double a0) {
    coefficients = new std::vector<double>();
    coefficients->push_back(a0);
    coefficients->push_back(a1);
    coefficients->push_back(a2);
    coefficients->push_back(a3);
    coefficients->push_back(a4);
}

Polynomial::~Polynomial() {
    delete coefficients;
}

double Polynomial::calculateCost(State *state) {
    double sum = 0;
    Variable *variable = dynamic_cast<Variable *>(state);
    double x = variable->getValue();
    double degreedX = 1;
    for (int i = 0; i < coefficients->size(); i++) {
        sum += coefficients->at(i) * degreedX;
        degreedX *= x;
    }
    return sum;
}
