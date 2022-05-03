#include "indicator_gpio.h"


/*
 * Pins PA0:PA11 are output 10 MHz push-pull
 * PA0 - a
 * PA1 - b
 * PA2 - c
 * PA3 - d
 * PA4 - e
 * PA5 - f
 * PA6 - g
 * PA7 - :
 * PA8 - digit 1
 * PA9 - digit 2
 * PA10 - digit 3
 * PA11 - digit 4
 */
void indicator_gpio_init()
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL |= GPIO_CRL_MODE0_0|\
                GPIO_CRL_MODE1_0|\
                GPIO_CRL_MODE2_0|\
                GPIO_CRL_MODE3_0|\
                GPIO_CRL_MODE4_0|\
                GPIO_CRL_MODE5_0|\
                GPIO_CRL_MODE6_0|\
                GPIO_CRL_MODE7_0;
    GPIOA->CRH |= GPIO_CRH_MODE8_0|\
                GPIO_CRH_MODE9_0|\
                GPIO_CRH_MODE10_0|\
                GPIO_CRH_MODE11_0;
    GPIOA->CRL &= ~(GPIO_CRL_CNF0|\
                    GPIO_CRL_CNF1|\
                    GPIO_CRL_CNF2|\
                    GPIO_CRL_CNF3|\
                    GPIO_CRL_CNF4|\
                    GPIO_CRL_CNF5|\
                    GPIO_CRL_CNF6|\
                    GPIO_CRL_CNF7);
    GPIOA->CRH &= ~(GPIO_CRH_CNF8|\
                    GPIO_CRH_CNF9|\
                    GPIO_CRH_CNF10|\
                    GPIO_CRH_CNF11);
    GPIOA->BSRR = 0x0FFF;
}