# Compiler and flags
CXX ?= g++
CXXFLAGS = -std=c++17 -Wall -Wextra
OPTFLAGS = -O2
DEBUGFLAGS = -g
LDFLAGS = -lstdc++fs  # Link filesystem library

# Directories
SRC_DIR = .
BUILD_DIR = build
RESULTS_DIR = results

# Executable name
TARGET = $(BUILD_DIR)/program

# Source and header files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/HammingDistance.cpp $(SRC_DIR)/testing.cpp
HEADERS = $(SRC_DIR)/HammingDistance.hpp $(SRC_DIR)/testing.hpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default build (release)
all: CXXFLAGS += $(OPTFLAGS)
all: $(BUILD_DIR) $(RESULTS_DIR) $(TARGET)

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(BUILD_DIR) $(RESULTS_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(RESULTS_DIR):
	mkdir -p $(RESULTS_DIR)

# Link objects
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile each .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(RESULTS_DIR)/*.csv

.PHONY: all debug clean