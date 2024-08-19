# Define the compiler and flags
CXX := g++
CXXFLAGS := -Wall -g -Iinclude	

# Define the source and include directories
SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj

# Find all the .cpp files in the source directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Find all the .hpp files in the include directory
HEADERS := $(wildcard $(INCLUDE_DIR)/*.hpp)

# Generate object files from source files
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Define the executable file
EXEC := tp3.out 

# Default target
all: $(EXEC)

# Rule to link the object files and create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Run the executable
run: $(EXEC)
	./$(EXEC) -b geracarga.base -e geracarga.ev

# Phony targets
.PHONY: all clean run
