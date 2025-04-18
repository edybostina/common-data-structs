# Compiler and flags
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I./include

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = tests
INCLUDE_DIR = include

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB = $(LIB_DIR)/libdata_structures.a
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC = $(TEST_DIR)/run_tests

# Targets

# Default target
all: $(LIB) $(EXEC)

# Create the static library
$(LIB): $(OBJ)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $^

# Rule to compile each .c file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile each test .c file into a .o file
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the tests with the static library to create the executable
$(EXEC): $(OBJ) $(TEST_OBJ) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

# Clean the generated files
clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB) $(EXEC)

# Remove everything including the directories
distclean: clean
	rm -rf $(OBJ_DIR) $(LIB_DIR)

# Rebuild the static library and tests from scratch
rebuild: distclean all
