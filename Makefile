########################################################################
# Author: Stevin Liang
#         This is a example Makefile for CortexM MCU using gnu arm gcc.
########################################################################
TARGET := example
TARGET_ELF := $(TARGET).elf
TARGET_HEX := $(TARGET).hex
TARGET_MAP := $(TARGET).map
TARGET_SIZE := $(TARGET).siz

CPU_CORE := cortex-m3
HOST_OS := $(shell lsb_release -d)
HOST_OS := $(patsubst Description:%, %, $(HOST_OS))
HOST_OS := $(strip $(HOST_OS))

CROSS_COMPILE := arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld
SIZE = $(CROSS_COMPILE)size
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

INCLUDES := -I ./usr/ -I ./system/cmsis/ -I ./system/inc/
LDSCRIPTS_DIR := ./ldscripts
LDSCRIPTS += -T mem.ld -T sections.ld

DIRS := $(shell find . -type d)
C_FILES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c, %.o, $(C_FILES))
OBJDS := $(patsubst %.c, %.d, $(C_FILES))

CFLAGS := -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char \
			-ffunction-sections -fdata-sections -ffreestanding \
			-flto -Werror -Wunused -Wuninitialized -Wall \
			-Wextra -Wpointer-arith -Wshadow -Wlogical-op \
			-Waggregate-return -Wfloat-equal  -g $(INCLUDES) \
			-std=gnu11 -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER \
			-Wbad-function-cast -MMD -MP

LDFLAGS := -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char \
			-ffunction-sections -fdata-sections -ffreestanding -flto \
			-Werror -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations \
			-Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op \
			-Waggregate-return -Wfloat-equal  -g $(LDSCRIPTS) \
			-nostartfiles -Xlinker --gc-sections -L"$(LDSCRIPTS_DIR)" \
			-Wl,-Map,"$(TARGET_MAP)" --specs=nano.specs

RM := rm -rf

SECONDARY_FLASH += $(TARGET_HEX)
SECONDARY_SIZE += $(TARGET_SIZE)

all: first-outputs $(TARGET_ELF) secondary-outputs

first-outputs:
	@echo '---------------------------------------------------'
	@echo '  Project Name:  $(TARGET)'
	@echo '  Cross Compile: $(CC)'
	@echo '  Target CORE:   $(CPU_CORE)'
	@echo '  Host OS:       $(HOST_OS)'
	@echo '---------------------------------------------------'
	@echo ''

%.o : %.c
	@echo '  CC      $@'
	@$(CC) $(CFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o $@ $<

$(TARGET_ELF): $(OBJS)
	@echo ' '
	@echo '  Linking target: $@'
	@echo '  Invoking: Cross ARM C Linker'
	@echo '  LD      $@'
	@$(CC) $(LDFLAGS) -o $@ $(OBJS)
	@echo '  Finished Link target: $@'
	@echo ' '

$(TARGET_HEX): $(TARGET_ELF)
	@echo '  Generating Flash Image'
	@echo '  Invoking: Cross ARM GNU Create Flash Image'
	@echo '  OBJCOPY      $@'
	@$(OBJCOPY) -O ihex $(TARGET_ELF) $(TARGET_HEX)
	@echo '  Finished Generate Flash Image: $@'
	@echo ' '

$(TARGET_SIZE): $(TARGET_ELF)
	@echo '  Invoking: Cross ARM GNU Print Size'
	@echo '  SIZE      $@'
	@$(SIZE) --format=berkeley $<
	@echo '  Finished building: $@'
	@echo ' '

# Other Targets

clean:
	@-$(RM) $(OBJS) $(OBJDS) $(TARGET_ELF) $(TARGET_HEX) $(TARGET_MAP)
	@echo '  CLEAN  $(TARGET) Done'

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean
