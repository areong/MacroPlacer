#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <vector>

class Utils {
public:
    Utils();
    ~Utils();
    /*
    Call this method before calling any random methods.
    */
    static void run_srand();
    /*
    Return random double in [0, 1).
    */
    static double random();
    /*
    Return random integer in [start, end).

    CAUTION: end > start
    */
    static int randint(int start, int end);
    /*
    Create and return a vector of integers in [start, end).
    The vector is SORTED.
    User should delete the vector after using it.
    
    CAUTION: end > start, and end - start < numInts

    WARNING: If end - start is large and numInts is also large,
    the loop inside this method might run for a long time.
    */
    static std::vector<int> *randints(int start, int end, int numInts);
    /*
    Return true or false randomly.
    */
    static bool randbool();
};

#endif