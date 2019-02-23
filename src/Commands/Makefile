CXX = g++
CXXFLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti \
			-nostdlib -nodefaultlibs -fno-leading-underscore -std=c++11
SRC_NAME = CommandsManager.cpp RebootCmd.cpp GodGiveCmd.cpp GodTakeCmd.cpp
INCLUDE_PATH = ../../include
COMMANDS_INCLUDE_PATH = ../../include/Commands
OBJ_PATH = obj/
KOBJ_PATH = ../../obj

OBJ_NAME = $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -I $(COMMANDS_INCLUDE_PATH) -c $^ -o $@

install: $(OBJ)
	@echo "Install CommandsManager objects..."
	@mkdir -p $(KOBJ_PATH)
	@/bin/cp $(OBJ_PATH)/*  $(KOBJ_PATH)

clean:
	@/bin/rm -rf $(OBJ_PATH)

re: clean all

.PHONY: all install clean re
