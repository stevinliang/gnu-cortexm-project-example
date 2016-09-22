########################################################################
# Author: Stevin Liang
#         This is a example Makefile for CortexM MCU using gnu arm gcc.
########################################################################
TARGET := example
TARGET_ELF := $(TARGET).elf
TARGET_HEX := $(TARGET).hex
TARGET_MAP := $(TARGET).map
TARGET_SIZE := $(TARGET).siz

CROSS_COMPILE := arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld
SIZE = $(CROSS_COMPILE)size
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

CFLAGS += -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char \
			-ffunction-sections -fdata-sections -ffreestanding -flto \
			-fno-move-loop-invariants -Wunused -Wuninitialized \
			-Wextra -Wpointer-arith \
			-Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  \
			-g3 -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER \
			-std=gnu11  \
			-Wbad-function-cast -MMD -MP 

LDSCRIPTS += -T mem.ld -T sections.ld 
LDSCRIPTS_DIR := ./ldscripts
LDFLAGS += -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char \
			-ffunction-sections -fdata-sections -ffreestanding -flto \
			-fno-move-loop-invariants -Werror -Wunused -Wuninitialized \
			-Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith \
			-Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  \
			-g3 $(LDSCRIPTS) -nostartfiles -Xlinker --gc-sections -L"$(LDSCRIPTS_DIR)" \
			-Wl,-Map,"$(TARGET_MAP)" --specs=nano.specs
INCLUDES += -I ./usr/ -I ./system/cmsis/ -I ./system/inc/

DIRS := $(shell find . -type d)
C_FILES := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c, %.o, $(C_FILES))
OBJDS := $(patsubst %.c, %.d, $(C_FILES))

RM := rm -rf

SECONDARY_FLASH += $(TARGET_HEX)
SECONDARY_SIZE += $(TARGET_SIZE)

all: $(TARGET_ELF) secondary-outputs

%.o : %.c
	@echo $(CC) $< -o $@ 
	@$(CC) $(CFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o $@ $<
	@echo ' '

$(TARGET_ELF): $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	@echo LD $@ 
	@$(CC) $(LDFLAGS) -o $@ $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

$(TARGET_HEX): $(TARGET_ELF)
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	$(OBJCOPY) -O ihex $(TARGET_ELF) $(TARGET_HEX)
	@echo 'Finished building: $@'
	@echo ' '

$(TARGET_SIZE): $(TARGET_ELF)
	@echo 'Invoking: Cross ARM GNU Print Size'
	$(SIZE) --format=berkeley $<
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets

clean:
	@-$(RM) $(OBJS) $(OBJDS) $(TARGET_ELF) $(TARGET_HEX) $(TARGET_MAP)

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean
