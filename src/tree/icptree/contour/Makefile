CC = g++
PATH_TO_SRC = ./../../../
INC = -I ${PATH_TO_SRC}

HEADERS_CONTOUR = \
	${PATH_TO_SRC}tree/icptree/contour/Contour.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

HEADERS_CONTOUR_TEST = \
	${PATH_TO_SRC}tree/icptree/contour/Contour_test.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h\
	${PATH_TO_SRC}tree/icptree/contour/Contour.h\
	${PATH_TO_SRC}tree/icptree/contour/TopContour.h\
	${PATH_TO_SRC}tree/icptree/contour/BottomContour.h\
	${PATH_TO_SRC}tree/icptree/contour/RightContour.h\
	${PATH_TO_SRC}tree/icptree/contour/LeftContour.h

HEADERS_EDGE = \
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

HEADERS_TOPCONTOUR = \
	${PATH_TO_SRC}tree/icptree/contour/Contour.h\
	${PATH_TO_SRC}tree/icptree/contour/TopContour.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

HEADERS_BOTTOMCONTOUR = \
	${PATH_TO_SRC}tree/icptree/contour/Contour.h\
	${PATH_TO_SRC}tree/icptree/contour/BottomContour.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

HEADERS_RIGHTCONTOUR = \
	${PATH_TO_SRC}tree/icptree/contour/Contour.h\
	${PATH_TO_SRC}tree/icptree/contour/RightContour.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

HEADERS_LEFTCONTOUR = \
	${PATH_TO_SRC}tree/icptree/contour/Contour.h\
	${PATH_TO_SRC}tree/icptree/contour/LeftContour.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/contour/Edge.h

all:
	make Contour.o
	make Contour_test.o
	make Edge.o
	make TopContour.o
	make BottomContour.o
	make RightContour.o
	make LeftContour.o
Contour.o: Contour.cpp ${HEADERS_CONTOUR}
	${CC} -c Contour.cpp ${INC}
Contour_test.o: Contour_test.cpp ${HEADERS_CONTOUR_TEST}
	${CC} -c Contour_test.cpp ${INC}
Edge.o: Edge.cpp ${HEADERS_EDGE}
	${CC} -c Edge.cpp ${INC}
TopContour.o: TopContour.cpp ${HEADERS_TOPCONTOUR}
	${CC} -c TopContour.cpp ${INC}
BottomContour.o: BottomContour.cpp ${HEADERS_BOTTOMCONTOUR}
	${CC} -c BottomContour.cpp ${INC}
RightContour.o: RightContour.cpp ${HEADERS_RIGHTCONTOUR}
	${CC} -c RightContour.cpp ${INC}
LeftContour.o:  LeftContour.cpp ${HEADERS_LEFTCONTOUR}
	${CC} -c LeftContour.cpp ${INC}
clean:
	rm *.o