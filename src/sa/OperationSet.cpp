#include "sa/OperationSet.h"
#include "utils/Utils.h"

OperationSet::OperationSet() {
    operations = new std::vector<Operation *>();
}

OperationSet::~OperationSet() {
    delete operations;
}

void OperationSet::addOperation(Operation *operation) {
    operations->push_back(operation);
}

void OperationSet::operate(State *state) {
    operations->at(Utils::randint(0, operations->size()))->operate(state);
}
