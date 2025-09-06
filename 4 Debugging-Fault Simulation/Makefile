# Makefile for Debugging & Fault Simulation System

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O2
LDFLAGS =

# Detect OS for platform-specific flags
ifeq ($(OS),Windows_NT)
    TARGET = debug_fault_sim.exe
    CFLAGS += -D_WIN32
else
    TARGET = debug_fault_sim
    LDFLAGS += -lm
endif

# Source files
SRC = debug_fault_sim.c
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET) system_debug.log

# Clean and rebuild
rebuild: clean all

# Debug build with symbols
debug: CFLAGS += -g -DDEBUG
debug: clean all

# Run the program
run: all
	./$(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the executable (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and rebuild"
	@echo "  debug    - Build with debug symbols"
	@echo "  run      - Build and run the program"
	@echo "  help     - Show this help message"

.PHONY: all clean rebuild debug run help
