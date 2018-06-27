ASM = nasm
ASM_FLAGS = -f elf32
CXX = g++
CXXFLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti \
			-nostdlib -nodefaultlibs -fno-leading-underscore
LD_PARAMS = -m elf_i386

SRC_PATH = src/

SRC_NAME = main.cpp VgaBuffer.cpp
ASM_SRC_NAME = loader.s

OBJ_PATH = obj/

OBJ_NAME = $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

ASM_OBJ_NAME = $(ASM_SRC_NAME:.s=.o)
ASM_OBJ = $(addprefix $(OBJ_PATH), $(ASM_OBJ_NAME))

EXEC = kernelito.bin

all: $(EXEC)

$(EXEC): $(OBJ) $(ASM_OBJ)
	@echo "Creating $(EXEC)..."
	@ld $(LD_PARAMS) -T linker.ld -o $(EXEC) $(OBJ) $(ASM_OBJ)
	@echo "$(EXEC) created."

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@make -C $(SRC_PATH)/VgaBuffer install
	@$(CXX) $(CXXFLAGS) -I include -c $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.s
	@$(ASM) $(ASM_FLAGS) $^ -o $@

install: $(EXEC)
	@echo "Install $(EXEC)..."
	@/bin/cp $(EXEC) /boot

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@echo "Objects removed."

fclean: clean
	@/bin/rm -f $(EXEC)
	@echo "$(EXEC) removed."

re: fclean all

.PHONY: all install clean fclean re
