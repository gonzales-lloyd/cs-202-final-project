#Made with help from the following Stack Overflow links:
#https://stackoverflow.com/questions/11394659/where-does-the-value-of-cxx-in-a-makefile-come-from/11394799 - helped fix $(CPPFLAGS) vs $(CXXFLAGS)
#https://stackoverflow.com/questions/30573481/how-to-write-a-makefile-with-separate-source-and-header-directories - go here for explanation
# - Lloyd Gonzales

#use `make obj/*.o` for intermediate object files

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .

EXE := $(BIN_DIR)/wav_manager
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXXFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR) wav_manager

-include $(OBJ:.o=.d)