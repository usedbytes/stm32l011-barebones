TARGET = blink

SOURCES = main.c startup.c system/system_stm32l0xx.c

OUTDIR = out
OBJS = $(patsubst %.c,$(OUTDIR)/%.o,$(SOURCES))

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

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(OUTDIR)
	rm $(TARGET).elf
	rm $(TARGET).hex
	rm $(TARGET).bin
