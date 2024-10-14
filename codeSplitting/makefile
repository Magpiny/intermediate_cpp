# Define the compiler and the C++ standard version
CXX = clang++
CXXSTD = -std=c++23
CXXFLAGS = -pthread

# Define the output directory and the executable name
BIN_DIR = bin
EXECUTABLE = APP
TARGET = $(BIN_DIR)/app

# Define the source file
SOURCE = intro.cc

# Create the bin directory if it doesn't exist
.PHONY: create_bin_dir
create_bin_dir:
	@mkdir -p $(BIN_DIR)
	
# Compile and link the source file into an executable
#$(TARGET): $(SOURCE) | create_bin_dir
	#$(CXX) $(CXXFLAGS) $(CXXSTD) -I./intro $< -o $@

bin/app: intro.cc intro/calc.cc | create_bin_dir
	$(CXX) $(CXXFLAGS) $(CXXSTD) -I./intro $^ -o $@ 
	
# Default target: compile, create bin directory, and run the executable
all: $(TARGET)
	./$(TARGET)
	
# Clean up the executable and bin directory
clean:
	-rm -rf $(BIN_DIR)
	
# Phony target to ensure targets are always executed
.PHONY: all clean create_bin_dir
