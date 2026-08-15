# ============================================
# Student Management System - Makefile
# ============================================

# Use ">" as the recipe prefix so TAB characters
# are not required in this file.
.RECIPEPREFIX := >

# --------------------------------------------
# Compiler
# --------------------------------------------

CC = gcc

# --------------------------------------------
# Compiler flags
# --------------------------------------------

CFLAGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wstrict-prototypes -std=c17

# --------------------------------------------
# Preprocessor flags
# --------------------------------------------

CPPFLAGS = -Iinclude

# --------------------------------------------
# Source and header files
# --------------------------------------------

SOURCES = src/main.c src/student.c src/input.c

HEADERS = include/input.h include/student.h

# --------------------------------------------
# Build configuration
# --------------------------------------------

BUILD_DIR = bin

TARGET = $(BUILD_DIR)/student_manager.exe

# --------------------------------------------
# Default target
# --------------------------------------------

all: $(TARGET)

# --------------------------------------------
# Build application
# --------------------------------------------

$(TARGET): $(SOURCES) $(HEADERS)
>if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
>$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) -o $(TARGET)

# --------------------------------------------
# Run application
# --------------------------------------------

run: $(TARGET)
>$(TARGET)

# --------------------------------------------
# Clean build files
# --------------------------------------------

clean:
>if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

# --------------------------------------------
# Rebuild application from scratch
# --------------------------------------------

rebuild: clean all

# --------------------------------------------
# Phony targets
# --------------------------------------------

.PHONY: all run clean rebuild