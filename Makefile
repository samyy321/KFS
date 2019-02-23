ASM = nasm
ASM_FLAGS = -f elf32
CXX = g++
CXXFLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti \
			-nostdlib -nodefaultlibs -fno-leading-underscore -std=c++11
LD_PARAMS = -m elf_i386

SRC_PATH = src/

SRC_NAME = main.cpp VgaBuffer.cpp GlobalDescriptorTable.cpp MemLib.cpp \
			InterruptsManager.cpp KbdHandler.cpp DisplayablesManager.cpp \
			Shell.cpp String.cpp Utils.cpp Print.cpp CommandsManager.cpp \
			GodGiveCmd.cpp GodTakeCmd.cpp RebootCmd.cpp
ASM_SRC_NAME = loader.s portIO.s interrupts.s

INCLUDE_PATH = include
COMMANDS_INCLUDE_PATH = include/Commands

OBJ_PATH = obj/

OBJ_NAME = $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

ASM_OBJ_NAME = $(ASM_SRC_NAME:.s=.o)
ASM_OBJ = $(addprefix $(OBJ_PATH), $(ASM_OBJ_NAME))

EXEC = kernelito.bin
GRUB_CFG = grub.cfg
ISO = kernelito.iso

all: $(EXEC)

$(EXEC): $(OBJ) $(ASM_OBJ)
	@echo "Creating $(EXEC)..."
	@ld $(LD_PARAMS) -T linker.ld -o $(EXEC) $(OBJ) $(ASM_OBJ)
	@echo "$(EXEC) created."

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@make -C lib/ install
	@make -C $(SRC_PATH)/VgaBuffer install
	@make -C $(SRC_PATH)/GlobalDescriptorTable install
	@make -C $(SRC_PATH)/Interrupts install
	@make -C $(SRC_PATH)/KbdHandler install
	@make -C $(SRC_PATH)/DisplayablesManager install
	@make -C $(SRC_PATH)/Shell install
	@make -C $(SRC_PATH)/Commands install
	@$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -I $(COMMANDS_INCLUDE_PATH) -c $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.s
	@$(ASM) $(ASM_FLAGS) $^ -o $@

install: $(EXEC)
	@echo "Install $(EXEC)..."
	@mkdir -p imgfiles/boot/grub/
	@/bin/cp $(GRUB_CFG) imgfiles/boot/grub/
	@/bin/cp $(EXEC) imgfiles/boot/
	@grub-mkrescue -o $(ISO) imgfiles
	@/bin/rm -rf imgfiles

run: $(ISO)
	@qemu-system-i386 -cdrom $(ISO)

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@make -C $(SRC_PATH)/VgaBuffer clean
	@make -C lib/ clean
	@make -C $(SRC_PATH)/GlobalDescriptorTable clean
	@make -C $(SRC_PATH)/Interrupts clean
	@make -C $(SRC_PATH)/KbdHandler clean
	@make -C $(SRC_PATH)/DisplayablesManager clean
	@make -C $(SRC_PATH)/Shell clean
	@make -C $(SRC_PATH)/Commands clean
	@echo "Objects removed."

fclean: clean
	@/bin/rm -f $(EXEC)
	@echo "$(EXEC) removed."
	@/bin/rm -f $(ISO)
	@echo "$(ISO) removed."

re: fclean all

.PHONY: all install clean fclean re
