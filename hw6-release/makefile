#
# Makefile for Pset 6: Trees
#
# CPSC 223
# Spring 2024
#

CXX      = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra
LDFLAGS  = -g

LIBS 	 = BSTNode.o BSTNodeChecker.o BSTNodePrinter.o

all: bst avlt rbt

bst: main_bst.o BSTree.o $(LIBS)
	${CXX} ${LDFLAGS} -o $@ $^

avlt: main_avlt.o AVLTree.o $(LIBS)
	${CXX} ${LDFLAGS} -o $@ $^

rbt: main_rbt.o RBTree.o $(LIBS)
	${CXX} ${LDFLAGS} -o $@ $^

clean:
	${RM} bst avlt rbt *.o *.dSYM

.PHONY: all clean
