CC = g++
OBJ = \
	model/*.o\
	model/sa/*.o\
	sa/*.o\
	tree/binarytree/*.o\
	tree/icptree/*.o\
	tree/icptree/contour/*.o\
	tree/icptree/sa/*.o\
	utils/*.o\
	view/*.o

HEADERS_MAIN = \
	sa/SimulatedAnnealing_test.h\
	tree/binarytree/BinaryTree_test.h\
	tree/icptree/ICPTree_test.h\
	tree/icptree/contour/Contour_test.h\
	utils/Utils.h\
	utils/Utils_test.h\
	view/FloorplanWindow_test.h

LIBS = -lGL -lglut

all:
	cd model; make all
	cd model/sa; make all
	cd sa; make all
	cd tree/binarytree; make all
	cd tree/icptree; make all
	cd tree/icptree/contour; make all
	cd tree/icptree/sa; make all
	cd utils; make all
	cd view; make all
	make placer
placer: main.o ${OBJ}
	# Please place -l after the object files.
	${CC} main.o ${OBJ} ${LIBS} -o placer
main.o: main.cpp ${HEADERS_MAIN}
	${CC} -c main.cpp
clean:
	cd model; make clean
	cd model/sa; make clean
	cd sa; make clean
	cd tree/binarytree; make clean
	cd tree/icptree; make clean
	cd tree/icptree/contour; make clean
	cd tree/icptree/sa; make clean
	cd utils; make clean
	cd view; make clean
	rm *.o placer