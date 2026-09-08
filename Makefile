# ============================================================
# BareMetalDrivers - Makefile
# Target: ARM Cortex-M4
# ============================================================

# ------------------------------------------------------------
# Toolchain
# ------------------------------------------------------------

CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# ------------------------------------------------------------
# Project
# ------------------------------------------------------------

TARGET = firmware

BUILD_DIR = build

# ------------------------------------------------------------
# CPU / Architecture
# ------------------------------------------------------------

CPU = cortex-m4

CFLAGS = \
	-mcpu=$(CPU) \
	-mthumb \
	-mfloat-abi=soft \
	-ffreestanding \
	-fno-builtin \
	-Wall \
	-Wextra \
	-g

ASFLAGS = \
	-mcpu=$(CPU) \
	-mthumb \
	-g

LDFLAGS = \
	-mcpu=$(CPU) \
	-T linker/linker.ld \
	-nostartfiles \
	-nodefaultlibs \
	-nostdlib \
	-Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# ------------------------------------------------------------
# Source Files
# ------------------------------------------------------------

C_SOURCES = \
	main.c \
	drivers/system.c \
	drivers/rcc.c \
	drivers/gpio.c \
	drivers/uart.c \
	drivers/systick.c \
	drivers/timer.c \
	drivers/nvic.c \
	drivers/exti.c

ASM_SOURCES = \
	startup/startup.s

# ------------------------------------------------------------
# Object Files
# ------------------------------------------------------------

C_OBJECTS = $(C_SOURCES:%.c=$(BUILD_DIR)/%.o)

ASM_OBJECTS = $(ASM_SOURCES:%.s=$(BUILD_DIR)/%.o)

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# ------------------------------------------------------------
# Default Target
# ------------------------------------------------------------

all: $(BUILD_DIR)/$(TARGET).elf \
     $(BUILD_DIR)/$(TARGET).bin

# ------------------------------------------------------------
# Compile C
# ------------------------------------------------------------

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# ------------------------------------------------------------
# Assemble
# ------------------------------------------------------------

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# ------------------------------------------------------------
# Link
# ------------------------------------------------------------

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(SIZE) $@

# ------------------------------------------------------------
# Generate Binary
# ------------------------------------------------------------

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# ------------------------------------------------------------
# Clean
# ------------------------------------------------------------

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean