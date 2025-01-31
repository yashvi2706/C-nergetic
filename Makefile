# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Directories
SRC_DIR = .                       # Root directory where everything is located
OUTPUT_DIR = $(SRC_DIR)/test        # Directory for test files

# Object files (List all your object files here)
OBJS = Code_Snippets/Star_Ratings/rating.o \
       Code_Snippets/String_Alignment/f_string.o \
       MAIN/Login.o \
       MAIN/Billing.o

# Final executable
TARGET = $(OUTPUT_DIR)/main

# Default target
all: $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^          # Compile and link all object files into the final executable

# Rules to compile each source file into object files
Code_Snippets/Star_Ratings/rating.o: Code_Snippets/Star_Ratings/rating.c Code_Snippets/Star_Ratings/rating.h
	$(CC) $(CFLAGS) -c $< -o $@

Code_Snippets/String_Alignment/f_string.o: Code_Snippets/String_Alignment/f_string.c Code_Snippets/String_Alignment/f_string.h
	$(CC) $(CFLAGS) -c $< -o $@

MAIN/Login.o: MAIN/Login.c
	$(CC) $(CFLAGS) -c $< -o $@

MAIN/Billing.o: MAIN/Billing.c
	$(CC) $(CFLAGS) -c $< -o $@

# # Rule for running the tests (assuming you have test.c in the test directory)
# test: $(TEST_DIR)/test.o $(OBJS)
# 	$(CC) $(CFLAGS) -o $(TEST_DIR)/test $(TEST_DIR)/test.o $(OBJS)

# $(TEST_DIR)/test.o: $(TEST_DIR)/test.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OUTPUT_DIR) $(TEST_DIR)/*.o $(TEST_DIR)/test $(OBJS)

# Phony targets (make sure these aren't confused with files)
.PHONY: all clean test
