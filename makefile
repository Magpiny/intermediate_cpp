# Define the compiler and the C++ standard version
CXX = g++
CXXSTD = -std=c++23

# Define the output directory and the executable name
BIN_DIR = bin
EXECUTABLE = $(BIN_DIR)/app

# Define the source file
SOURCE = app.cpp

# Create the bin directory if it doesn't exist
.PHONY: create_bin_dir
create_bin_dir:
    @mkdir -p $(BIN_DIR)

# Compile and link the source file into an executable
$(EXECUTABLE): $(SOURCE) | create_bin_dir
    $(CXX) $(CXXFLAGS) $(CXXSTD) $< -o $@

# Default target: compile, create bin directory, and run the executable
all: $(EXECUTABLE)
    $(EXECUTABLE)

# Clean up the executable and bin directory
clean:
    -rm -f $(EXECUTABLE)
    -rmdir $(BIN_DIR)

# Phony target to ensure targets are always executed
.PHONY: all clean create_bin_dir
