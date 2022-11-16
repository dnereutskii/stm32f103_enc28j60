# path to STM32F103 standard peripheral library
# STD_PERIPH_LIBS ?= ./STM32F10x_StdPeriph_Lib_V3.5.0/

# list of source files
SOURCES  = main.c
SOURCES += cmsis/src/system_stm32f1xx.c
SOURCES += core/enc28j60/enc28j60.c
SOURCES += core/enc28j60/spi/enc28j60_spi.c
SOURCES += core/delay/delay.c
SOURCES += core/buart/buart.c
SOURCES += core/tcp_ip/1network/ethernet.c
SOURCES += core/tcp_ip/1network/arp.c
SOURCES += core/tcp_ip/2internet/ip.c
SOURCES += core/tcp_ip/2internet/icmp.c
SOURCES += core/tcp_ip/3transport/udp.c
SOURCES += core/tcp_ip/4application/lan.c

# add startup file to build
SOURCES += ./startup/startup_stm32f103xb.s

# name for output binary files
PROJECT ?= test

# compiler, objcopy (should be in PATH)
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# path to st-flash (or should be specified in PATH)
ST_FLASH ?= st-flash
# ST_FLASH ?= ST-LINK_CLI
ST_INFO = st-info

# specify compiler flags
CFLAGS  = -g -O0 -Wall
CFLAGS += -T ./startup/STM32F103XB_FLASH.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork
CFLAGS += -DSTM32F103xB
CFLAGS += -Wl,--gc-sections
CFLAGS += -I.
CFLAGS += -I ./cmsis/inc/
# main header
CFLAGS += -I ./core
# delay header
CFLAGS += -I ./core/delay/
# burat header
CFLAGS += -I ./core/buart/
# enc28j60 headers 
CFLAGS += -I ./core/enc28j60/
CFLAGS += -I ./core/enc28j60/spi
# tcp_ip headers 
CFLAGS += -I ./core/tcp_ip
CFLAGS += -I ./core/tcp_ip/1network
CFLAGS += -I ./core/tcp_ip/2internet
CFLAGS += -I ./core/tcp_ip/3transport
CFLAGS += -I ./core/tcp_ip/4application


OBJS = $(SOURCES:.c=.o)

all: $(PROJECT).elf size

# compile
$(PROJECT).elf: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

# remove binary files
clean:
	rm -f *.o *.elf *.hex *.bin

# flash
burn:
	$(ST_FLASH) write $(PROJECT).bin 0x8000000
# $(ST_FLASH) -c SWD -P $(PROJECT).hex 0x8000000 -Rst

# size info
size:
	@$(SIZE) -B -d ./$(PROJECT).elf

# MCU info
info:
	@$(ST_INFO) --probe

