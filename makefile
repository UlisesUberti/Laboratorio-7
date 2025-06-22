SRC_DIR = ./src
INC_DIR = ./inc ./modules/inc

OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/OBJ
BIN_DIR = $(OUT_DIR)/bin
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=C99

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
-include $(OBJ_DIR)/*.d
all: $(OBJ_FILES)
	@echo "Linking object files to create the executable"
	@mkdir -p $(BIN_DIR)
	@gcc $(OBJ_FILES) -o $(BIN_DIR)/app.exe

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 	
	@echo "Compilate $< to $@"
	@mkdir -p $(OBJ_DIR)
	@gcc -o $@ -c $< $(foreach DIR,$(INC_DIR),-I $(DIR)) -MMD -D CANTIDAD_MAXIMA_ALUMNOS=1
	
clean:
	@rm -rf $(OUT_DIR)
	
doc:
	@echo "Generando documentación con Doxygen..."
	@mkdir -p build/doc
	@doxygen Doxyfile