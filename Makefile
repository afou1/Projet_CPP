CXX=g++
CXXFLAGS=-Wall -O2 -std=c++11


SUPP=rm
EXEC=annuaire
ARCHIVE=projet.zip

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all:$(EXEC)


$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@
zip:
	zip $(ARCHIVE) $(SRC) $(HEADERS)
clean:
	$(SUPP) -f $(OBJ)
mrproper: clean
	$(SUPP) -f $(EXEC)
