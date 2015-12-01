CROSS= arm-unknown-eabi-

CC= $(CROSS)gcc
LD= $(CROSS)ld
OBJCOPY= $(CROSS)objcopy
OBJDUMP= $(CROSS)objdump
SIZE= $(CROSS)size
READELF= $(CROSS)readelf

# libgcc.a
LIBS = -L/home/ryota/cross/rpi/arm-unknown-eabi/lib/gcc/arm-unknown-eabi/4.9.1/
# newlib
LIBS += -L/home/ryota/cross/rpi/arm-unknown-eabi/arm-unknown-eabi/lib/
STARTUP= startup.o
OBJS= main.o

# systemcall
OBJS += syscalls.o

# RaspberryPi library
OBJS+= rpi_lib/rpi_init.o rpi_lib/gpio/gpio.o rpi_lib/timer/timer.o rpi_lib/delay/delay.o rpi_lib/i2s/i2s.o rpi_lib/i2c/i2c1.o rpi_lib/serial/serial.o
OBJS+= rpi_lib/bss/clearbss.o


# interrupt
OBJS += rpi_lib/interrupt.o

CFLAGS= -mfloat-abi=hard -mlittle-endian
CFLAGS+= -nostartfiles
CFLAGS+= -ffreestanding
CFLAGS+= -Ofast
CFLAGS+= -marm -mcpu=arm1176jzf-s 
CFLAGS+= -lm
CFLAGS+= -mfpu=vfp

########################
all:	rpi-micon.img

rpi-micon.elf:	$(STARTUP) $(OBJS)
	$(LD) -static -nostartfiles -T rpiMicon.lds $^ -o $@ $(LIBS) -lc -lm -lgcc
	$(OBJDUMP) -D rpi-micon.elf > rpi-micon.disas
	$(SIZE) rpi-micon.elf > rpi-micon.size
	$(READELF) -a rpi-micon.elf > rpi-micon.readelf

.SUFFIXES: .elf .img

.elf.img:
	$(OBJCOPY) -O binary $< $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
.S.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean::
	$(RM) -f *.o *.img *.elf */*.o */*/*.o 
	$(RM) -f tags *~

tags::
	ctags *.[chS]
