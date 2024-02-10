# path to STM32F103 standard peripheral library
# STD_PERIPH_LIBS ?= ./STM32F10x_StdPeriph_Lib_V3.5.0/

# Name for output binary files
PROJECT = test

# Compiler, objcopy (should be in PATH)
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
DBG = arm-none-eabi-gdb

# Path to st-flash (or should be specified in PATH)
ST_FLASH = st-flash
ST_UTIL = st_util
#ST_LINK = ST-LINK_CLI
ST_INFO = st-info
OCD = openocd

# List of source files
SRCS = ./startup/startup_stm32f103xb.s
SRCS += main.c
SRCS += cmsis/src/system_stm32f1xx.c
SRCS += core/enc28j60/enc28j60.c
SRCS += core/enc28j60/enc28j60_spi.c
SRCS += core/delay/delay.c
SRCS += core/buart/buart.c
SRCS += core/tcp_ip/lan.c
SRCS += core/tcp_ip/1network/ethernet.c
SRCS += core/tcp_ip/1network/arp.c
SRCS += core/tcp_ip/2internet/ip.c
SRCS += core/tcp_ip/2internet/icmp.c
SRCS += core/tcp_ip/3transport/udp.c
SRCS += core/tcp_ip/4application/ntp.c

# CMSIS headers
INCLUDE_DIRS = -I./cmsis/inc/
# main header
INCLUDE_DIRS += -I./core
# delay header
INCLUDE_DIRS += -I./core/delay/
# burat header
INCLUDE_DIRS += -I./core/buart/
# enc28j60 headers 
INCLUDE_DIRS += -I./core/enc28j60/
# tcp_ip headers 
INCLUDE_DIRS += -I./core/tcp_ip
INCLUDE_DIRS += -I./core/tcp_ip/1network
INCLUDE_DIRS += -I./core/tcp_ip/2internet
INCLUDE_DIRS += -I./core/tcp_ip/3transport
INCLUDE_DIRS += -I./core/tcp_ip/4application

# specify compiler flags
CFLAGS  = -g -O0 -Wall
CFLAGS += -T ./startup/STM32F103XB_FLASH.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections,--no-warn-rwx-segments

# Preprocessor flags
CPPFLAGS = -DSTM32F103xB
CPPFLAGS += $(INCLUDE_DIRS)

# Objects
OBJS = $(SRCS:.c=.o)

all: $(PROJECT).elf $(PROJECT).bin size

# Compile
$(PROJECT).elf: $(SRCS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -O ihex $< $(PROJECT).hex

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $(PROJECT).bin

# remove binary files
clean:
	rm -f *.o *.elf *.hex *.bin

# flash
burn:
	$(ST_FLASH) write $(PROJECT).bin 0x8000000

burn_win:
	$(ST_LINK) -c SWD -P $(PROJECT).hex 0x8000000 -Rst

ocd_burn:
	$(OCD) -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
	-f /usr/share/openocd/scripts/target/stm32f1x.cfg -c \
	"init; reset halt; flash write_image erase test.hex; reset; exit"

debug:
	$(DBG) $(PROJECT).elf \
	-ex 'target remote localhost:3333' \
	-ex 'monitor reset halt'
# -ex 'tui enable'

ocd_open:
	$(OCD) -f /usr/share/openocd/scripts/interface/stlink-v2.cfg \
	-f /usr/share/openocd/scripts/target/stm32f1x.cfg \
# -l ./ocd_log &

ocd_open_win:
	$(OCD) -f "C:/xpack-openocd-0.11.0-5/scripts/interface/stlink-v2.cfg" \
	-f "C:/xpack-openocd-0.11.0-5/scripts/target/stm32f1x.cfg" \
# -l ./ocd_log &

ocd_burn_win:
	$(OCD) -f "C:/xpack-openocd-0.11.0-5/scripts/interface/stlink-v2.cfg" \
	-f "C:/xpack-openocd-0.11.0-5/scripts/target/stm32f1x.cfg" \
	-c "init; reset halt; flash write_image erase test.hex; reset; exit"

# size info
size:
	@$(SIZE) -B -d ./$(PROJECT).elf

# MCU info
info:
	@$(ST_INFO) --probe


