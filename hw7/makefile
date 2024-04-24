CXX = g++
CXXFLAGS = -g -pedantic -std=c++17 -Wall
DEPS = Graph.hpp MinQueue.hpp traits.hpp

EXE = graph-main

${EXE} : main.o
	${CXX} ${CXXFLAGS} -o $@ $<

main.o : main.cpp ${DEPS}
	${CXX} ${CXXFLAGS} -c -o $@ $<

clean:
	$(RM) *.o ${EXE}
