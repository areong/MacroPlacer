CC = g++
PATH_TO_SRC = ./../../
INC = -I ${PATH_TO_SRC}

HEADERS_ICPTREE = \
	${PATH_TO_SRC}tree/binarytree/BinaryTree.h\
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}utils/Utils.h

HEADERS_ICPTREE_TEST = \
	${PATH_TO_SRC}tree/icptree/ICPTree.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskPrintIdAndIdentity.h

HEADERS_MACRONODE = \
	${PATH_TO_SRC}tree/binarytree/Node.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorLeftFirst.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorRightFirst.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorRightOnly.h

HEADERS_TRAVERSALTASKPRINTIDANDIDENTITY = \
	${PATH_TO_SRC}tree/binarytree/TraversalTask.h\
	${PATH_TO_SRC}tree/icptree/TraversalTaskPrintIdAndIdentity.h\
	${PATH_TO_SRC}tree/icptree/MacroNode.h

all:
	make ICPTree.o
	make ICPTree_test.o
	make MacroNode.o
	make TraversalTaskPrintIdAndIdentity.o
ICPTree.o: ICPTree.cpp ${HEADERS_ICPTREE}
	${CC} -c ICPTree.cpp ${INC}
ICPTree_test.o: ICPTree_test.cpp ${HEADERS_ICPTREE}
	${CC} -c ICPTree_test.cpp ${INC}
MacroNode.o: MacroNode.cpp ${HEADERS_MACRONODE}
	${CC} -c MacroNode.cpp ${INC}
TraversalTaskPrintIdAndIdentity.o: TraversalTaskPrintIdAndIdentity.cpp ${HEADERS_TRAVERSALTASKPRINTIDANDIDENTITY}
	${CC} -c TraversalTaskPrintIdAndIdentity.cpp ${INC}