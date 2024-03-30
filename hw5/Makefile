#
#  Makefile
#  CPSC 223 Pset 5
#
#  Makefile for treasure-hunter.cpp, LinkedList and Island
#


CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
DEPS = Island.h LinkedList.h

treasure-hunter: treasure-hunter.o Island.o LinkedList.o
	$(CXX) -o treasure-hunter treasure-hunter.o Island.o LinkedList.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.o core* *~ treasure-hunter
