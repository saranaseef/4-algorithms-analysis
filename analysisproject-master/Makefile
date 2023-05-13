CC=g++
INC_DIR= ./headers
SRC_DIR= ./src
OBJ_DIR= ./obj
OBJECTS= $(subst $(SRC_DIR), $(OBJ_DIR), $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp)))
CCFLAGS= -I$(INC_DIR)/

all: StringMatching

StringMatching:	$(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o StringMatching

.PHONY: Dir
Dir: 
	mkdir $(OBJ_DIR)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) -c $(CCFLAGS)  $< -o $@
	
.PHONY: clean
clean: 
	$(RM) $(OBJECTS)
