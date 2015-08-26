CC = g++
PATH_TO_SRC = ./../
INC = -I ${PATH_TO_SRC}

HEADERS_FLOORPLANVIEW = \
	${PATH_TO_SRC}view/View.h\
	${PATH_TO_SRC}view/FloorplanView.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}view/TraversalTaskDrawMacroNode.h\
	${PATH_TO_SRC}view/Window.h

HEADERS_FLOORPLANWINDOW = \
	${PATH_TO_SRC}view/Window.h\
	${PATH_TO_SRC}view/FloorplanWindow.h\
	${PATH_TO_SRC}model/Floorplan.h\
	${PATH_TO_SRC}view/FloorplanView.h

HEADERS_FLOORPLANWINDOW_TEST = \
	${PATH_TO_SRC}view/FloorplanWindow.h

HEADERS_MACROVIEW = \
	${PATH_TO_SRC}view/View.h\
	${PATH_TO_SRC}view/MacroView.h\
	${PATH_TO_SRC}model/Macro.h\
	${PATH_TO_SRC}view/Window.h

HEADERS_TRAVERSALTASKDRAWMACRONODE = \
	${PATH_TO_SRC}tree/binarytree/TraversalTask.h\
	${PATH_TO_SRC}view/TraversalTaskDrawMacroNode.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}view/MacroView.h

HEADERS_VIEW = \
	${PATH_TO_SRC}view/View.h

HEADERS_WINDOW = \
	${PATH_TO_SRC}view/Window.h

all:
	make FloorplanView.o
	make FloorplanWindow.o
	make FloorplanWindow_test.o
	make MacroView.o
	make TraversalTaskDrawMacroNode.o
	make View.o
	make Window.o
FloorplanView.o: FloorplanView.cpp ${HEADERS_FLOORPLANVIEW}
	${CC} -c FloorplanView.cpp ${INC}
FloorplanWindow.o: FloorplanWindow.cpp ${HEADERS_FLOORPLANWINDOW}
	${CC} -c FloorplanWindow.cpp ${INC}
FloorplanWindow_test.o: FloorplanWindow_test.cpp ${HEADERS_FLOORPLANWINDOW_TEST}
	${CC} -c FloorplanWindow_test.cpp ${INC}
MacroView.o: MacroView.cpp ${HEADERS_MACROVIEW}
	${CC} -c MacroView.cpp ${INC}
TraversalTaskDrawMacroNode.o: TraversalTaskDrawMacroNode.cpp ${HEADERS_TRAVERSALTASKDRAWMACRONODE}
	${CC} -c TraversalTaskDrawMacroNode.cpp ${INC}
View.o: View.cpp ${HEADERS_VIEW}
	${CC} -c View.cpp ${INC}
Window.o: Window.cpp ${HEADERS_WINDOW}
	${CC} -c Window.cpp ${INC}