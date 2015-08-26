#include "utils/Utils.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Utils::Utils() {

}

Utils::~Utils() {

}

void Utils::run_srand() {
    srand(time(0));
}

double Utils::random() {
    return (double) rand() / ((double) RAND_MAX + 1);
}

int Utils::randint(int start, int end) {
    int range = end - start;
    return (int) ((double) rand() / ((double) RAND_MAX + 1) * range) + start;
}

std::vector<int> *Utils::randints(int start, int end, int numInts) {    
    std::vector<int> *ints = new std::vector<int>();
    for (int i = 0; i < numInts; i++) {
        int result;
        bool chosen;
        do {
            // Choose a random int.
            result = Utils::randint(start, end);
            // Check already chosen or not.
            chosen = false;
            for (int j = 0; j < ints->size(); j++) {
                if (result == ints->at(j)) {
                    chosen = true;
                    break;
                }
            }
        } while (chosen);
        ints->push_back(result);
    }
    std::sort(ints->begin(), ints->end());
    return ints;
}

bool Utils::randbool() {
    double result = (double) rand() / ((double) RAND_MAX + 1);
    if (result >= 0.5)
        return true;
    else
        return false;
}
