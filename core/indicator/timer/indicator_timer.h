#ifndef __INDICATOR_TIMER_H
#define __INDICATOR_TIMER_H


#include <stm32f1xx.h>


// #define TIMER_IT_UPDATE() TIM2->DIER |= TIM_DIER_UIE    /*Update interrupt enabled*/
#define TIMER_Enable() TIM2->CR1 |= TIM_CR1_CEN         /*Counter enabled*/
#define TIMER_Disable() TIM2->CR1 &= ~TIM_CR1_CEN       /*Counter disabled*/


void indicator_timer_init(uint16_t prs, uint16_t cntt);


#endif  /*__INDICATOR_TIMER_H*/