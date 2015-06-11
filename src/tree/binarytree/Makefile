CC = g++
PATH_TO_SRC = ./../../
INC = -I ${PATH_TO_SRC}

HEADERS_BINARYTREE = \
	${PATH_TO_SRC}tree/binarytree/BinaryTree.h\
	${PATH_TO_SRC}tree/binarytree/Node.h\
	${PATH_TO_SRC}tree/binarytree/TraversalTask.h

HEADERS_BINARYTREE_TEST = \
	${PATH_TO_SRC}tree/binarytree/BinaryTree_test.h\
	${PATH_TO_SRC}tree/binarytree/BinaryTree.h\
	${PATH_TO_SRC}tree/binarytree/Node.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorRightFirst.h\
	${PATH_TO_SRC}tree/binarytree/TraversalTaskPrintId.h

HEADERS_NEXTNODESBEHAVIORLEFTFIRST = \
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorLeftFirst.h\
	${PATH_TO_SRC}tree/binarytree/Node.h

HEADERS_NEXTNODESBEHAVIORNONEXT = \
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorNoNext.h

HEADERS_NEXTNODESBEHAVIORRIGHTFIRST = \
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorRightFirst.h\
	${PATH_TO_SRC}tree/binarytree/Node.h

HEADERS_NODE = \
	${PATH_TO_SRC}tree/binarytree/Node.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehavior.h\
	${PATH_TO_SRC}tree/binarytree/NextNodesBehaviorLeftFirst.h

HEADERS_TRAVERSALTASKPRINTID = \
	${PATH_TO_SRC}tree/binarytree/TraversalTaskPrintId.h\
	${PATH_TO_SRC}tree/binarytree/Node.h

all:
	make BinaryTree.o
	make BinaryTree_test.o
	make NextNodesBehaviorLeftFirst.o
	make NextNodesBehaviorNoNext.o
	make NextNodesBehaviorRightFirst.o
	make Node.o
	make TraversalTaskPrintId.o
BinaryTree.o: BinaryTree.cpp ${HEADERS_BINARYTREE}
	${CC} -c BinaryTree.cpp ${INC}
BinaryTree_test.o: BinaryTree_test.cpp ${HEADERS_BINARYTREE_TEST}
	${CC} -c BinaryTree_test.cpp ${INC}
NextNodesBehaviorLeftFirst.o: NextNodesBehaviorLeftFirst.cpp ${HEADERS_NEXTNODESBEHAVIORLEFTFIRST}
	${CC} -c NextNodesBehaviorLeftFirst.cpp ${INC}
NextNodesBehaviorNoNext.o: NextNodesBehaviorNoNext.cpp ${HEADERS_NEXTNODESBEHAVIORNONEXT}
	${CC} -c NextNodesBehaviorNoNext.cpp ${INC}
NextNodesBehaviorRightFirst.o: NextNodesBehaviorRightFirst.cpp ${HEADERS_NEXTNODESBEHAVIORRIGHTFIRST}
	${CC} -c NextNodesBehaviorRightFirst.cpp ${INC}
Node.o: Node.cpp ${HEADERS_NODE}
	${CC} -c Node.cpp ${INC}
TraversalTaskPrintId.o: TraversalTaskPrintId.cpp ${HEADERS_TRAVERSALTASKPRINTID}
	${CC} -c TraversalTaskPrintId.cpp ${INC}