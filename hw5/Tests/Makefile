#
#  Makefile
#  CPSC 223
#  Spring 2023
#
#  Makefile for testing script
#

# -----------------------------------------------------------------------------
# Directory in which to search for source files. You may change this here, or
# pass the directory as the first argument to tests.sh (the value passed to
# tests.sh takes precedence over this one).

SRCDIR ?= $(shell pwd)

# Source files that you made. Add any others that you created for this Pset.
LIBS = Island.cpp LinkedList.cpp

# -----------------------------------------------------------------------------

# Compiler variables and options. DO NOT CHANGE!
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -g

# Source files that we made. DO NOT CHANGE!
MAINS = unittest.cpp treasure-hunter.cpp

# Variables. DO NOT CHANGE!
MOBJS = $(MAINS:.cpp=.o)
BINS = $(MAINS:.cpp=)
DEPS = $(LIBS:.cpp=.h)
OBJS = $(LIBS:.cpp=.o)

all: $(BINS)

$(OBJS):%.o: $(addprefix $(SRCDIR)/, %.cpp) $(DEPS)
	@echo "Compiling $< with SRCDIR = $(SRCDIR)"
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(MOBJS):%.o: %.cpp $(DEPS)

$(BINS):%: %.o $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) $(BINS)
	$(RM) $(MOBJS) $(OBJS)
	$(RM) core* *~

.PHONY: all clean
