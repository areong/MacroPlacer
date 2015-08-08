#include "tree/binarytree/BinaryTree_test.h"
#include "tree/icptree/ICPTree_test.h"
#include "tree/icptree/contour/Contour_test.h"
#include "utils/Utils.h"
#include "utils/Utils_test.h"
#include "view/FloorplanWindow_test.h"

int main(int argc, char **argv) {
    Utils::run_srand();
    //testBinaryTree();
    //testUtils();
    testICPTree();
    //testContour();
    //testFloorplanWindow();
    return 0;
}