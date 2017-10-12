################################################################################
# PRIME NUMBERS SEARCHING ALGORITHM
# Ver. 1.3
#
# Syntax: make [ list | primeq | all | clean ]
#
# Copyleft 2014 Victor Manuel Fernandez Castro - All rights revoked.
# January 2nd 2014.
################################################################################

BIN = bin
SRC = .

CXX			= g++ -std=c++11
CXXFLAGS	= -pipe -Wall -O3 -fopenmp
LIBS		= -lsqlite3
MKDIR		= mkdir -p
RMFILE		= rm -f

TARGET	= $(BIN)/list $(BIN)/primeq $(BIN)/eratosthenes

.PHONY: all pre clean

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: pre $(TARGET)

pre:
	$(MKDIR) $(BIN)

clean:
	$(RMFILE) $(TARGET)

$(BIN)/list: $(SRC)/list.cpp $(SRC)/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(BIN)/primeq: $(SRC)/primeq.cpp $(SRC)/common.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(BIN)/eratosthenes: $(SRC)/eratosthenes.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(SRC)/list.cpp: $(SRC)/common.h
$(SRC)/primeq.cpp: $(SRC)/common.h
$(SRC)/common.cpp: $(SRC)/common.h
