#ifndef MODEL_FLOORPLAN_TEST_H_
#define MODEL_FLOORPLAN_TEST_H_

void testFloorplan_addMacrosToBins();

void testFloorplan_readAux(int argc, char **argv);

/*
argv[1]: input aux filename
argv[2]: output pl filename
*/
void testFloorplan_outputPlForPrototyping(int argc, char **argv);

void testFloorplan(int argc, char **argv);

#endif