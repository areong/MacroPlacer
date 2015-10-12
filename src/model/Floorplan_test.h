#ifndef MODEL_FLOORPLAN_TEST_H_
#define MODEL_FLOORPLAN_TEST_H_

void testFloorplan_addMacrosToBins();

void testFloorplan_readAux(int argc, char **argv);

/*
argv[1]: input aux filename
argv[2]: output nodes filename
argv[3]: output pl filename
*/
void testFloorplan_outputForPrototyping(int argc, char **argv);

/*
argv[1]: intput aux filename
argv[2]: intput pl filename (the prototype)
argv[3]: output nodes filename
argv[4]: output pl filename
argv[5]: output fp filename
*/
void testFloorplan_readPrototypeAndOutputItForEvaluation(int argc, char **argv);

void testFloorplan(int argc, char **argv);

#endif