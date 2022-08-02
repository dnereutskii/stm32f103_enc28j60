#include "stm32f1xx.h"
#include "delay.h"


void delay_init(void)
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}


__INLINE void delay_us(uint32_t us)
{
	uint32_t us_count_tick =  us * (SystemCoreClock / 1000000U);
	DWT->CYCCNT = 0U;
	while(DWT->CYCCNT < us_count_tick){}
}


__INLINE void delay_ms(uint32_t ms)
{
	uint32_t ms_count_tick =  ms * (SystemCoreClock / 1000U);
	DWT->CYCCNT = 0U;
	while(DWT->CYCCNT < ms_count_tick){}
}