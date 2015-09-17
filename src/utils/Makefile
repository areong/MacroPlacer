CC = g++
PATH_TO_SRC = ./../
INC = -I ${PATH_TO_SRC}

HEADERS_UTILS = \
	${PATH_TO_SRC}utils/Utils.h

HEADERS_UTILS_TEST = \
	${PATH_TO_SRC}utils/Utils.h\
	${PATH_TO_SRC}utils/Utils_test.h

all:
	make Utils.o
	make Utils_test.o
Utils.o: Utils.cpp ${HEADERS_UTILS}
	${CC} -c Utils.cpp ${INC}
Utils_test.o: Utils_test.cpp ${HEADERS_UTILS_TEST}
	${CC} -c Utils_test.cpp ${INC}