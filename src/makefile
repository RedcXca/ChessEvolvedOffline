CXX=g++
CXXFLAGS=-std=c++20 -pedantic -Wall -Wextra -g -MMD
EXEC=chess
CCFILES=$(wildcard *.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11 -lpng
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
