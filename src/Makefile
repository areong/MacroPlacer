CC = g++
OBJ = \
	model/*.o\
	tree/binarytree/*.o\
	tree/icptree/*.o\
	tree/icptree/contour/*.o\
	utils/*.o

HEADERS_MAIN = \
	tree/binarytree/BinaryTree_test.h\
	tree/icptree/ICPTree_test.h\
	tree/icptree/contour/Contour_test.h\
	utils/Utils.h\
	utils/Utils_test.h

all:
	cd model; make all
	cd tree/binarytree; make all
	cd tree/icptree; make all
	cd tree/icptree/contour; make all
	cd utils; make all
	make placer
placer: main.o ${OBJ}
	${CC} -o placer main.o ${OBJ}
main.o: main.cpp ${HEADERS_MAIN}
	${CC} -c main.cpp
