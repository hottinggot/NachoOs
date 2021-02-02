ARCH = armv7-a
MCPU = cortex-a8

TARGET = rvpb

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./nachoos.ld
MAP_FILE = build/nachoos.map

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.os, $(ASM_SRCS))

VPATH = boot \
	hal/$(TARGET) \
	lib	\
	kernel

C_SRCS = $(notdir $(wildcard boot/*.c))
C_SRCS += $(notdir $(wildcard hal/$(TARGET)/*.c))
C_SRCS += $(notdir $(wildcard kernel/*.c))
C_SRCS += $(notdir $(wildcard lib/*.c))
C_OBJS = $(patsubst %.c, build/%.o, $(C_SRCS))

INC_DIRS = -I include	\
	   -I hal	\
	   -I hal/$(TARGET)	\
	   -I lib	\
	   -I kernel

CFLAGS = -c -g -std=c11
LDFLAGS = -nostartfiles -nostdlib -nodefaultlibs -static -lgcc

nachoos = build/nachoos.axf
nachoos_bin = build/nachoos.bin

.PHONY: all clean run debug gdb

all: $(nachoos)

clean:
	@rm -fr build

run: $(nachoos)
	qemu-system-arm -M realview-pb-a8 -kernel $(nachoos) -nographic

debug: $(nachoos)
	qemu-system-arm -M realview-pb-a8 -kernel $(nachoos) -S -gdb tcp::1234,ipv4

gdb:
	gdb-multiarch

$(nachoos): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $(nachoos) $(ASM_OBJS) $(C_OBJS) -Wl,-Map=$(MAP_FILE) $(LDFLAGS)
	$(OC) -O binary $(nachoos) $(nachoos_bin)

build/%.os: %.S
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<

build/%.o: %.c
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<

