# UDP server on STM32F103C8 and ENC28J60

## Sources
- [STM3232F103C8 reference manual](https://www.st.com/resource/en/reference_manual/-008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-us-stmicroelectronics.pdf)

## Burn firmware
openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f1x.cfg -c "init; reset halt; flash write_image erase test.hex; reset; exit"

### Fire up OpenOCD
openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f1x.cfg