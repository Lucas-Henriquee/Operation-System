# Compiler
CXX := g++

# Directories
SRC_DIR := source
INCLUDE_DIR := include
BUILD_DIR := build

# Source files
SOURCE_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SRC := main.cpp

# Combine all source files
SRCS := $(SOURCE_SRCS) $(MAIN_SRC)

# Object files
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(subst /,_, $(SRCS)))

# Header files 
DEPS := $(wildcard $(INCLUDE_DIR)/*.hpp)

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INCLUDE_DIR)

# OS-specific commands
ifeq ($(OS),Windows_NT)
    TARGET := scheduler_exec.exe
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) & if exist $(TARGET) del $(TARGET)
else
    TARGET := scheduler_exec
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET)
endif

.PHONY: all clean

all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile Rules
$(BUILD_DIR)/source_%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for the main.cpp file 
$(BUILD_DIR)/main.o: main.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM_CMD)