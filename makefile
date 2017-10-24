
# --------------------------------------------------- #
# makefile
# compile lab3 executable
# --------------------------------------------------- #

# variables

PROG = vigenere
OBJS = vigenere.o
CXX = g++
DEBUG = -g
WARN = -Wall
LDFLAGS = $(WARN) $(DEBUG)
CXXFLAGS = -c $(WARN) $(DEBUG)

# --------------------------------------------------- #

# executable

$(PROG) : $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(PROG)

# object files

vigenere.o : vigenere.cpp
	$(CXX) $(CXXFLAGS) vigenere.cpp

# --------------------------------------------------- #

# clean

clean :
	rm -f $(PROG) $(OBJS)
