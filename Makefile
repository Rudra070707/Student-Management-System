# ============================================
# Student Management System - Makefile
# ============================================

# Use ">" as the recipe prefix so TAB characters
# are not required in this file.
.RECIPEPREFIX := >

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -std=c17

# Preprocessor flags
CPPFLAGS = -Iinclude

# Source files
SOURCES = src/main.c src/student.c src/input.c

# Header files
HEADERS = include/input.h include/student.h

# Build directory
BUILD_DIR = bin

# Output executable
TARGET = $(BUILD_DIR)/student_manager.exe

# Default target
all: $(TARGET)

# Build application
$(TARGET): $(SOURCES) $(HEADERS)
>mkdir -p $(BUILD_DIR)
>$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) -o $(TARGET)

# Run application
run: $(TARGET)
>./$(TARGET)

# Clean build files
clean:
>rm -rf $(BUILD_DIR)

# Rebuild application from scratch
rebuild: clean all

# Phony targets
.PHONY: all run clean rebuild
