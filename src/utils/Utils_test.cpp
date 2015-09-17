#include "utils/Utils_test.h"
#include <iostream>
#include <vector>
#include "utils/Utils.h"

void testUtils() {
    std::cout << "randint(4, 11): " << Utils::randint(4, 11) << std::endl;
    std::vector<int> *ints = Utils::randints(4, 11, 5);
    std::cout << "randints(4, 11, 5): ";
    for (int i = 0; i < ints->size(); i++)
        std::cout << ints->at(i) << " ";
    std::cout << "\n";
    std::cout << "randbool(): " << Utils::randbool() << std::endl;
    delete ints;

    std::vector<std::string> *stringTokens = Utils::splitString("o0\t8 12\tc r\t4", "\t");
    for (int i = 0; i < stringTokens->size(); ++i) {
        std::cout << stringTokens->at(i) << ", ";
    }
    std::cout << "\n";
    delete stringTokens;
}