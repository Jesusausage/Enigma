EXE = enigma
SRC = main.cpp enigma.cpp enigma-errors.cpp rotor.cpp rotor-errors.cpp fidelis.cpp
OBJ = $(SRC:%.cpp=%.o)
DEP = $(OBJ:%.o=%.d)
FLAGS = -Wall -g -MMD -c

$(EXE): $(OBJ)
	g++ $^ -o $@

%.o: %.cpp
	g++ $(FLAGS) $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(EXE)

.PHONY: clean
