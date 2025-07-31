# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -Iinclude

# Directories
SRC_DIR := source
INCLUDE_DIR := include
BUILD_DIR := build
TARGET := scheduler_exec

# Source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
OBJ_FILES += $(BUILD_DIR)/main.o

# OS-specific commands
ifeq ($(OS),Windows_NT)
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) & if exist $(TARGET) del $(TARGET)
else
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET)
endif

.PHONY: all clean

all: $(TARGET)

# Link object files
$(TARGET): $(OBJ_FILES)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Compilation successful: $(TARGET) built!"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR_CMD)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main separately
$(BUILD_DIR)/main.o: main.cpp
	@$(MKDIR_CMD)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	@$(RM_CMD)