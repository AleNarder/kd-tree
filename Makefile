# Compiler settings
CXX := g++
CXXFLAGS := -Wall -Wextra -Iinclude

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Find all .cpp source files
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Generate corresponding .o filenames
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

# Output executable name
EXECUTABLE := $(BIN_DIR)/kd-tree

# Default target
all: $(BIN_DIR) $(BUILD_DIR) $(EXECUTABLE)

# Rule to create the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile .cpp files to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build and bin directories if they don't exist
$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(EXECUTABLE)
