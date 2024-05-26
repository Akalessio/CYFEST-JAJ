# Compiler settings
CC = gcc
CFLAGS = -std=c11 -Iinclude

# Source files
SRC = main.c salle.c fonx.c sauvefichier.c place.c

# Object files (automatically derived from the source files)
OBJ = $(SRC:.c=.o)

# Executable name
EXEC = CYFEST

# Default target
all: $(EXEC)

# Rule to link the object files into the final executable
$(EXEC): $(OBJ)
	@echo "Linking $(EXEC) with $(OBJ)"
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Rule to compile source files into object files
%.o: %.c
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
    rm -f $(EXEC) $(OBJ)

# Phony targets to avoid conflicts with files named 'all' or 'clean'
.PHONY: all clean

