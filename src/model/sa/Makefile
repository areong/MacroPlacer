CC = g++
PATH_TO_SRC = ./../../
INC = -I ${PATH_TO_SRC}

HEADERS_COUNTOFMOVABLEMACROSOUTSIDEDESIREDREGION = \
	${PATH_TO_SRC}sa/CostFunction.h\
	${PATH_TO_SRC}model/sa/CountOfMovableMacrosOutsideDesiredRegion.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}tree/icptree/sa/FloorplanState.h

all:
	make CountOfMovableMacrosOutsideDesiredRegion.o
CountOfMovableMacrosOutsideDesiredRegion.o: CountOfMovableMacrosOutsideDesiredRegion.cpp ${HEADERS_COUNTOFMOVABLEMACROSOUTSIDEDESIREDREGION}
	${CC} -c CountOfMovableMacrosOutsideDesiredRegion.cpp ${INC}