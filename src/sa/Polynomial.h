#ifndef SA_POLYNOMIAL_H_
#define SA_POLYNOMIAL_H_

#include "sa/CostFunction.h"
#include <vector>

/*
The class is for testing sa/.
It only takes Variable as State.
*/
class Polynomial : public CostFunction {
public:
    Polynomial(double a4, double a3, double a2, double a1, double a0);
    ~Polynomial();
    /*
    @Override
    @param state A Variable.
    */
    double calculateCost(State *state);

private:
    std::vector<double> *coefficients;
};
  
#endif