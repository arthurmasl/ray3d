# Compiler
CC := gcc

# Directories
SRC_DIR := src
BUILD_DIR := build

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
EXECUTABLE := $(BUILD_DIR)/game

# Flags
CFLAGS := -Wall -I. -I$(SRC_DIR)
LDFLAGS := -lraylib -framework OpenGL -framework OpenAL -framework Cocoa -framework IOKit -framework CoreVideo

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)
