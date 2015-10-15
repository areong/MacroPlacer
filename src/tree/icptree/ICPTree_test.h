#ifndef TREE_ICPTREE_TEST_H_
#define TREE_ICPTREE_TEST_H_

void testICPTree_intialize01();

void testICPTree_intialize02();

void testICPTree_placeMacrosNoNormalNorSwitch();

void testICPTree_placeMacrosRandomlyNoSwitch();

/*
For real benchmarks,
argv[1]: input aux file
argv[2]: input pl file of prototype
*/
void testICPTree_anneal(int argc, char **argv);

void testICPTree(int argc, char **argv);

#endif