# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SOURCES = Login.c f_string.c \
          Registration.c f_string.c \
          Admin.c f_string.c \
          Main.c f_string.c \
          ViewPage.c f_string.c \
          user_page.c f_string.c \
          selection.c f_string.c \
          Billing.c f_string.c

# Object files (same as source files but with .o extension)
OBJECTS = $(SOURCES:.c=.o)

# Output files
OUTPUTS = login registration admin main viewpage userpage selection billing

# Default target
all: $(OUTPUTS)

# Rule for building the output files
$(OUTPUTS): %: %.o f_string.o
	$(CC) $(CFLAGS) $^ -o $@

# Rule for compiling .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJECTS) $(OUTPUTS)
