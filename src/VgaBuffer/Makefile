CXX = g++
CXXFLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti \
			-nostdlib -nodefaultlibs -fno-leading-underscore
SRC_NAME = VgaBuffer.cpp
INCLUDE_PATH = ../../include
OBJ_PATH = obj/
KOBJ_PATH = ../../obj

OBJ_NAME = $(SRC_NAME:.cpp=.o)
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c $^ -o $@

install: $(OBJ)
	@echo "Install VgaBuffer objects..."
	@mkdir -p $(KOBJ_PATH)
	@/bin/cp $(OBJ_PATH)/*  $(KOBJ_PATH)

clean:
	@/bin/rm -rf $(OBJ_PATH)

re: clean all

.PHONY: all install clean re
