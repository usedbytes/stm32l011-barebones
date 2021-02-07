TARGET = blink

SOURCES = main.c startup.c system/system_stm32l0xx.c

OBJDIR := obj
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))

DEPDIR := $(OBJDIR)
DEPS := $(patsubst %.c,$(DEPDIR)/%.d,$(SOURCES))
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

INCLUDES = -Isystem/include -ICMSIS_5/CMSIS/Core/Include
LINKER_SCRIPT = stm32l011k4t6.ld

CFLAGS = -fno-common -mcpu=cortex-m0 -mthumb
CFLAGS += $(INCLUDES)
CFLAGS += -Wall -Wextra
LDFLAGS = -mcpu=cortex-m0 -mthumb -nostartfiles -T$(LINKER_SCRIPT)
ASFLAGS = -ahls -mcpu=cortex-m0 -mthumb

CROSS_COMPILE=arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy

.PHONY: all

all: $(TARGET).hex $(TARGET).bin $(TARGET).lss

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -R .stack -R .bss -O binary -S $< $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -R .stack -R .bss -O ihex $< $@

$(TARGET).lss: $(TARGET).elf
	$(OBJDUMP) -h -S $< > $@

$(TARGET).elf: $(OBJS) $(LINKER_SCRIPT)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d | $(DEPDIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(DEPDIR):
	@mkdir -p $(DEPDIR)

$(DEPS):

.PHONY: clean
clean:
	rm -r $(OBJDIR)
	rm $(TARGET).elf
	rm $(TARGET).hex
	rm $(TARGET).bin

include $(wildcard $(DEPS))
