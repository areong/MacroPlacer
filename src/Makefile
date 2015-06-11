CC = g++
OBJ = \
	tree/binarytree/*.o

HEADERS_MAIN = \
	tree/binarytree/BinaryTree_test.h

all:
	cd tree/binarytree; make all
	make placer
placer: main.o ${OBJ}
	${CC} -o placer main.o ${OBJ}
main.o: main.cpp ${HEADERS_MAIN}
	${CC} -c main.cpp
