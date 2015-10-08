#include "utils/Utils.h"
#include <cstdlib>
#include <cstring>
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

int Utils::getIndexOfLargestInVector(std::vector<int> *numbers) {
    int index = 0;
    int max = -1e8;
    for (int i = 0; i < numbers->size(); ++i) {
        if (numbers->at(i) > max) {
            max = numbers->at(i);
            index = i;
        }
    }
    return index;
}

std::vector<std::string> *Utils::splitString(std::string source, std::string splitter) {
    // http://www.cplusplus.com/reference/string/string/c_str/

    std::vector<std::string> *results = new std::vector<std::string>();
    char *charsSource = new char[source.length() + 1];
    char *charsSplitter = new char[splitter.length() + 1];
    std::strcpy(charsSource, source.c_str());
    std::strcpy(charsSplitter, splitter.c_str());
    char *token = std::strtok(charsSource, charsSplitter);
    while (token != 0) {
        results->push_back(std::string(token));
        token = std::strtok(NULL, charsSplitter);
    }
    delete[] charsSource;
    return results;
}