ASM = nasm
ASM_FLAGS = -f elf32
CXX = g++
CXXFLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti \
			-nostdlib -nodefaultlibs -fno-leading-underscore
SRC_NAME = InterruptsManager.cpp

ASM_SRC_NAME = interrupts.s

INCLUDE_PATH = ../../include
OBJ_PATH = obj/
KOBJ_PATH = ../../obj

ASM_OBJ_NAME = $(ASM_SRC_NAME:.s=.o)
ASM_OBJ = $(addprefix $(OBJ_PATH), $(ASM_OBJ_NAME))

OBJ_NAME = $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(ASM_OBJ) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.s
	@mkdir -p $(OBJ_PATH)
	@$(ASM) $(ASM_FLAGS) $^ -o $@

install: $(ASM_OBJ) $(OBJ)
	@echo "Install InterruptsManager objects..."
	@mkdir -p $(KOBJ_PATH)
	@/bin/cp $(OBJ_PATH)/*  $(KOBJ_PATH)

clean:
	@/bin/rm -rf $(OBJ_PATH)

re: clean all

.PHONY: all install clean re
