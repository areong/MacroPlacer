CC = g++
PATH_TO_SRC = ./../
INC = -I ${PATH_TO_SRC}

HEADERS_FLOORPLAN = \
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h

HEADERS_MACRO = \
	${PATH_TO_SRC}model/Macro.h

all:
	make Macro.o
	make Floorplan.o
Floorplan.o: Floorplan.cpp ${HEADERS_FLOORPLAN}
	${CC} -c Floorplan.cpp ${INC}
Macro.o: Macro.cpp ${HEADERS_MACRO}
	${CC} -c Macro.cpp ${INC}