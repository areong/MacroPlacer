#include "tree/binarytree/BinaryTree_test.h"
#include "tree/icptree/ICPTree_test.h"
#include "utils/Utils.h"
#include "utils/Utils_test.h"

int main(int argc, char **argv) {
    //testBinaryTree();
    Utils::run_srand();
    //testUtils();
    testICPTree();
    return 0;
}