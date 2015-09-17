CC = g++
PATH_TO_SRC = ./../
INC = -I ${PATH_TO_SRC}

HEADERS_BIN = \
	${PATH_TO_SRC}model/Bin.h

HEADERS_CELL = \
	${PATH_TO_SRC}model/Module.h\
	${PATH_TO_SRC}model/Cell.h

HEADERS_FLOORPLAN = \
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}model/Bin.h\
	${PATH_TO_SRC}model/Cell.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}model/Module.h\
	${PATH_TO_SRC}model/Net.h\
	${PATH_TO_SRC}model/Pin.h\
	${PATH_TO_SRC}model/Terminal.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}utils/Utils.h

HEADERS_FLOORPLAN_TEST = \
	${PATH_TO_SRC}model/Floorplan_test.h\
	${PATH_TO_SRC}model/Bin.h\
	${PATH_TO_SRC}model/Cell.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}model/Terminal.h\
	${PATH_TO_SRC}utils/Utils.h\
	${PATH_TO_SRC}view/FloorplanWindow.h

HEADERS_MACRO = \
	${PATH_TO_SRC}model/Module.h\
	${PATH_TO_SRC}model/Macro.h

HEADERS_MODULE = \
	${PATH_TO_SRC}model/Module.h\
	${PATH_TO_SRC}model/Pin.h

HEADERS_NET = \
	${PATH_TO_SRC}model/Net.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}model/Pin.h

HEADERS_PIN = \
	${PATH_TO_SRC}model/Pin.h

HEADERS_TERMINAL = \
	${PATH_TO_SRC}model/Module.h\
	${PATH_TO_SRC}model/Terminal.h\
	${PATH_TO_SRC}model/Pin.h

all:
	make Bin.o
	make Cell.o
	make Floorplan.o
	make Floorplan_test.o
	make Macro.o
	make Module.o
	make Net.o
	make Pin.o
	make Terminal.o
Bin.o: Bin.cpp ${HEADERS_BIN}
	${CC} -c Bin.cpp ${INC}
Cell.o: Cell.cpp ${HEADERS_CELL}
	${CC} -c Cell.cpp ${INC}
Floorplan.o: Floorplan.cpp ${HEADERS_FLOORPLAN}
	${CC} -c Floorplan.cpp ${INC}
Floorplan_test.o: Floorplan_test.cpp ${HEADERS_FLOORPLAN_TEST}
	${CC} -c Floorplan_test.cpp ${INC}
Macro.o: Macro.cpp ${HEADERS_MACRO}
	${CC} -c Macro.cpp ${INC}
Module.o: Module.cpp ${HEADERS_MODULE}
	${CC} -c Module.cpp ${INC}
Net.o: Net.cpp ${HEADERS_NET}
	${CC} -c Net.cpp ${INC}
Pin.o: Pin.cpp ${HEADERS_PIN}
	${CC} -c Pin.cpp ${INC}
Terminal.o: Terminal.cpp ${HEADERS_TERMINAL}
	${CC} -c Terminal.cpp ${INC}