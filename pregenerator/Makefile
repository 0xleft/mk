CXX = g++
Q = @

# Directories
SRC_DIR = ../src
PREGENERATOR_DIR = .
BUILD_DIR = target

$(shell mkdir -p $(BUILD_DIR)/chess)

# Source files
SRC = $(wildcard $(SRC_DIR)/chess/*.cpp)
PREGENERATOR_SRC = $(wildcard $(PREGENERATOR_DIR)/*.cpp)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
PREGENERATOR_OBJ = $(PREGENERATOR_SRC:$(PREGENERATOR_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Compiler flags
CPPFLAGS = -std=c++11 -fno-exceptions -O3 -Wall -I../include -I$(SRC_DIR) -I$(SRC_DIR)/engine -I$(SRC_DIR)/chess -ffunction-sections -fdata-sections

# Linker flags
LDFLAGS = -Wl,--gc-sections

# Targets
.PHONY: all clean

all: $(BUILD_DIR)/pregenerator


$(BUILD_DIR)/pregenerator: $(OBJ) $(PREGENERATOR_OBJ)
	$(Q) $(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(PREGENERATOR_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

run: $(BUILD_DIR)/pregenerator
	$(Q) $(BUILD_DIR)/pregenerator

clean:
	rm -rf $(BUILD_DIR)
	rm -rf hdmagics
	mkdir -p hdmagics