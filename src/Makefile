CC = g++
OBJ = \
	model/*.o\
	tree/binarytree/*.o\
	tree/icptree/*.o\
	tree/icptree/contour/*.o\
	utils/*.o\
	view/*.o

HEADERS_MAIN = \
	tree/binarytree/BinaryTree_test.h\
	tree/icptree/ICPTree_test.h\
	tree/icptree/contour/Contour_test.h\
	utils/Utils.h\
	utils/Utils_test.h\
	view/FloorplanWindow_test.h

LIBS = -lGL -lglut

all:
	cd model; make all
	cd tree/binarytree; make all
	cd tree/icptree; make all
	cd tree/icptree/contour; make all
	cd utils; make all
	cd view; make all
	make placer
placer: main.o ${OBJ}
	# Please place -l after the object files.
	${CC} main.o ${OBJ} ${LIBS} -o placer
main.o: main.cpp ${HEADERS_MAIN}
	${CC} -c main.cpp
