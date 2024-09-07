# Compiler
CC = arm-linux-gnueabihf

# Directories
SRC_DIR = ../src
INC_DIR = ../include
BUILD_DIR = .

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.s $(SRC_DIR)/*.S $(SRC_DIR)/*.c)
SRC_CFILES = $(wildcard $(SRC_DIR)/*.c)
SRC_sFILES = $(wildcard $(SRC_DIR)/*.s)
SRC_SFILES = $(wildcard $(SRC_DIR)/*.S)

# Object files
OBJ_FILES = $(SRC_sFILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)
OBJ_FILES += $(SRC_SFILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
OBJ_FILES += $(SRC_CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


# Target executable
TARGET = ledc.bin

# Compilation flags
CFLAGS = -I$(INC_DIR) -Wall -nostdlib

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CC)-ld -Timx6ul.lds -o $(BUILD_DIR)/ledc.elf $^
	$(CC)-objcopy -O binary -S $(BUILD_DIR)/ledc.elf $@
	$(CC)-objdump -D -m arm $(BUILD_DIR)/ledc.elf > $(BUILD_DIR)/ledc.dis

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC)-gcc $(CFLAGS) -c -O2 -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	$(CC)-gcc $(CFLAGS) -c -O2 -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	$(CC)-gcc $(CFLAGS) -c -O2 -o $@ $<

# Clean up
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) $(BUILD_DIR)/*.dis

# Print src and obj
print:
	@echo srcFiles: $(SRC_FILES)
	@echo objFiles: $(OBJ_FILES)
