#include "indicator.h"
#include "indicator_gpio.h"
#include "indicator_timer.h"

const uint8_t chars[] = {0xC0,    /*0*/
                    0xF9,   /*1*/
                    0xA4,   /*2*/
                    0xB0,   /*3*/
                    0x99,   /*4*/
                    0x92,   /*5*/
                    0x82,   /*6*/
                    0xF8,   /*7*/
                    0x80,   /*8*/
                    0x90,   /*9*/
                    0x7F,   /*:*/
                    0xFF,   /*None*/
};


volatile uint8_t digits[4];  /*digits buffer*/


/*
 * Timer 2 interrupt handler
 */
void TIM2_IRQHandler()
{   
    if(TIM2->SR&TIM_SR_UIF) /*if overflow interrupt flag*/
    {
        TIM2->SR &= ~TIM_SR_UIF;    /*clear interrupt flag*/
        indicator_update();
    }
}


void indicator_update()
{
    static uint8_t dig_order = 0U;
    GPIOA->BSRR = ((0xFF&~digits[dig_order])<<16)|(0xFF&digits[dig_order]);   /*write char to port*/
    if(dig_order == 0)
    {GPIOA->BSRR = GPIO_BSRR_BR8|GPIO_BSRR_BS9|GPIO_BSRR_BS10|GPIO_BSRR_BS11;}  /*switch on digit 1*/
    if(dig_order == 1)
    {GPIOA->BSRR = GPIO_BSRR_BS8|GPIO_BSRR_BR9|GPIO_BSRR_BS10|GPIO_BSRR_BS11;}  /*switch on digit 2*/
    if(dig_order == 2)
    {GPIOA->BSRR = GPIO_BSRR_BS8|GPIO_BSRR_BS9|GPIO_BSRR_BR10|GPIO_BSRR_BS11;}  /*switch on digit 3*/
    if(dig_order == 3)
    {GPIOA->BSRR = GPIO_BSRR_BS8|GPIO_BSRR_BS9|GPIO_BSRR_BS10|GPIO_BSRR_BR11;}  /*switch on digit 4*/
    dig_order++;
    if(dig_order > 3){dig_order = 0;}
}


/*
 * 7seg-indicator initialization
 */
void indicator_init()
{
    indicator_gpio_init();                /*gpio initialization*/
    indicator_timer_init(3599, 100);      /*5 ms overflow*/
    TIMER_Enable();                       /*timer start*/
    digits[0] = digits[1] = \
    digits[2] = digits[3] = chars[11];    /*clear digits*/
}


/*
 * Print number on 7seg-indicator
 */
void indicator_print_number(uint16_t number)
{
    if(number < 1000) {digits[0] = chars[11];} 
    else {digits[0] = chars[number/1000];}
    
    if(number < 100){digits[1] = chars[11];}
    else {digits[1] = chars[(number/100)%10];}

    if(number < 10){digits[2] = chars[11];}
    else {digits[2] = chars[(number/10)%10];}
    
    digits[3] = chars[number%10];
}
