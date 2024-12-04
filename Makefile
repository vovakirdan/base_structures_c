# Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11

# Directories
TEST_DIR = test
INCLUDE_DIR = include

# Test executables
VECTOR_TEST = $(TEST_DIR)/test_vector
DICT_TEST = $(TEST_DIR)/test_dict

.PHONY: all clean test test_vector test_dict

# Default target
all: $(VECTOR_TEST) $(DICT_TEST)

# Build vector test
$(VECTOR_TEST): $(TEST_DIR)/test_vector.c $(INCLUDE_DIR)/vector.h
	$(CC) $(CFLAGS) -o $(VECTOR_TEST) $(TEST_DIR)/test_vector.c

# Build dict test
$(DICT_TEST): $(TEST_DIR)/test_dict.c $(INCLUDE_DIR)/dict.h
	$(CC) $(CFLAGS) -o $(DICT_TEST) $(TEST_DIR)/test_dict.c

# Run both tests
test: test_vector test_dict

# Run vector test
test_vector: $(VECTOR_TEST)
	@echo "Running vector tests..."
	@$(VECTOR_TEST)

# Run dict test
test_dict: $(DICT_TEST)
	@echo "Running dict tests..."
	@$(DICT_TEST)

# Clean up generated files
clean:
	rm -f $(VECTOR_TEST) $(DICT_TEST)
