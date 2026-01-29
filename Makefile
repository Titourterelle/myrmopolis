CXX = g++
CXXFLAGS = -W -Wall -Wextra -Wfloat-equal -MMD -MP
EXEC = prog
SRC = $(wildcard src/*.cpp)
OBJ = $(notdir $(SRC:.cpp=.o))

all : $(EXEC)

%.o : src/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(EXEC) : $(OBJ)
	$(CXX) -o $@ $^

clean :
	rm -rf *.o *.d

rmproper : clean
	rm -rf $(EXEC)

-include $(OBJ:.o=.d)