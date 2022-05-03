#include "indicator_timer.h"


void indicator_timer_init(uint16_t prs, uint16_t cntt)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     /*timer 2 clock enabled*/
    NVIC_EnableIRQ(TIM2_IRQn);              /*global interrupt for timer 2*/
    TIM2->PSC = prs-1;                      /*prescaler*/
    TIM2->ARR = cntt;                       /*count to*/
    TIM2->DIER |= TIM_DIER_UIE;             /*Update interrupt enabled*/
}