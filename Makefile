# Compiler settings
CC = gcc
CFLAGS = -std=c11 -Iinclude

# Source files
SRC = main.c salle.c fonx.c sauvefichier.c place.c
# Header files
HDR = include/salle.h include/fonx.h include/sauvefichier.h include/place.h

# Executable name
EXEC = CYFEST

# Default target
all: $(EXEC)

# Compilation
$(EXEC): $(SRC) $(HDR)
    $(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# Clean
clean:
    rm -f $(EXEC)
