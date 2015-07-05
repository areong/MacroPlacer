CC = g++
PATH_TO_SRC = ./../
INC = -I ${PATH_TO_SRC}

HEADERS_MACRO = \
	${PATH_TO_SRC}model/Macro.h

all:
	make Macro.o
Macro.o: Macro.cpp ${HEADERS_MACRO}
	${CC} -c Macro.cpp ${INC}