# FOLLOW THE STEPS BELOW TO USE THIS MAKEFILE

# Compiler and flags
CXX = g++
# 1. INSERT -D<OPERATING SYSTEM> in CXXFLAGS. See README.MD for details.
CXXFLAGS = -DASIO_STANDALONE -fPIC -std=c++11 -Wall -Wextra -Werror -Wno-error=unused-parameter -Wno-error=unused-variable
LDFLAGS = -lpthread

# Directories
SRC_DIR = src
HEADER_DIR = headers
LIB_DIR = lib
BUILD_DIR = build

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# 2. ADJUST PATHS TO EXTERNAL LIBRARIES
ASIO_DIR = path/to/asio
JSON_DIR = path/to/json
WEBSOCKETPP_DIR = path/to/websocketpp

# Include directories for external libraries
ASIO_INCLUDE = -I$(ASIO_DIR)/include
JSON_INCLUDE = -I$(JSON_DIR)/include
WEBSOCKETPP_INCLUDE = -I$(WEBSOCKETPP_DIR)

# Target: YourLibrary.so (shared library)
LIB_NAME = Canvaspp
LIB_EXT = so  # Default extension for Unix-like systems
ifeq ($(OS), Windows_NT)
    LIB_EXT = dll  # Change to .dll for Windows
endif
LIB_SO = $(LIB_DIR)/lib$(LIB_NAME).$(LIB_EXT)

all: $(LIB_SO)

$(LIB_SO): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(ASIO_INCLUDE) $(JSON_INCLUDE) $(WEBSOCKETPP_INCLUDE) -I$(HEADER_DIR) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)

.PHONY: all clean