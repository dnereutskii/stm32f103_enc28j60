#include "stm32f1xx.h"
#include "delay.h"
#include "enc28j60.h"
#include "lan.h"
#include "buart.h"

#define ONE_MS      1000U       /*Delay milliseconds const*/
#define ONE_US      1000000U    /*Delay microseconds const*/

void delay(uint32_t tck);
void systick_init(uint32_t times);
void led_init();
void swd_init();
void clock_deinit();
void clock_init();

volatile uint32_t systick_cnt = 0U;
// uint8_t mac_addr[] = {0x00,0x13,0x37,0x01,0x23,0x45};


void SysTick_Handler()
{
    if(systick_cnt){systick_cnt--;}
}


int main()
{
    // uint8_t enc_revid = 0;
    uint8_t str[] = "str1\r\n";
    clock_init();
    swd_init();
    led_init();
    delay_init();
    uart_init(UART_RATE_9600);
    lan_init();
    // enc28j60_init(mac_addr);
    // enc_revid = enc28j60_rcr(EREVID);
    while(1)
    {
        // lan_poll();
        GPIOC->BSRR = GPIO_BSRR_BR13;//on led
        // GPIOC->ODR |= GPIO_ODR_ODR13;
        delay_ms(500);
        // uart_write('g');
        uart_write_string(str);
        // uart_write_data(str, sizeof(str)/sizeof(uint8_t));
        GPIOC->BSRR = GPIO_BSRR_BS13;//off led
        // GPIOC->ODR &= ~GPIO_ODR_ODR13;
        delay_ms(500);
    };

    return 0;
}


void led_init()
{
    // BIT_BAND_PER(RCC->APB2ENR, RCC_APB2ENR_IOPCEN) = 1;
    // BIT_BAND_PER(GPIOC->CRH, GPIO_CRH_MODE13) = 1;
    // BIT_BAND_PER(GPIOC->CRH, GPIO_CRH_CNF13_0) = 1;
    // BIT_BAND_PER(GPIOC->BSRR, GPIO_BSRR_BS13) = 1;



    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;             /*clock enable for GPIOC on APB2 bus*/
    GPIOC->CRH |= GPIO_CRH_MODE13|GPIO_CRH_CNF13_0; /*PC13 is output mode 50 MHz open-drain*/
    GPIOC->BSRR = GPIO_BSRR_BS13;                   /*off led*/

    // GPIOC->CRH |= GPIO_CRH_MODE14;                  /*PC14 is output mode 50 MHz*/
    // GPIOC->CRH &= ~GPIO_CRH_CNF14;                  /*PC14 is push-pull*/
    // GPIOC->BSRR = GPIO_BSRR_BR14;                   /*off led*/
}

void swd_init()
{
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; /*clock enable for AFIO on APB2 bus*/
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_1;  /*JTAG-DP Disabled and SW-DP Enabled*/
}


void clock_deinit()
{
    RCC->CR |= RCC_CR_HSION;            /*enable internal high-speed clock*/
    while(!(RCC->CR&RCC_CR_HSIRDY)){}   /*wait for HSI ready flag is set*/
    RCC->CR &= ~RCC_CR_HSITRIM; 
    RCC->CR |= 0x80U;                   /*reset internal high-speed clock trimming to default value 16*/
    RCC->CFGR = 0x00000000U;            /*clear configuration register*/
    while(RCC->CFGR&RCC_CFGR_SWS){}     /*wait for HSI oscillator used as system clock*/
    RCC->CR &= ~RCC_CR_PLLON;           /*disable PLL*/
    while(RCC->CR&RCC_CR_PLLRDY){}      /*wait for ready PLL flag clearing*/
    RCC->CR &= ~RCC_CR_HSEON;           /*disable HSE*/
    RCC->CR &= ~RCC_CR_CSSON;           /*disable clock detector*/
    while(RCC->CR&RCC_CR_HSERDY){}      /*wait for ready HSE flag clearing*/
    RCC->CR &= ~RCC_CR_HSEBYP;          /*disable bypass*/
    RCC->CSR |= RCC_CSR_RMVF;           /*remove all reset flags*/
    RCC->CIR = 0x00000000U;             /*reset clock interrupt register*/
}

/*
 * SYSCLK is clocked by 72 MHz
 * AHB is clocked by 72 MHz
 * APB1 is clocked by 36 MHz
 * APB2 is clocked by 72 MHz
 */
void clock_init()
{
    RCC->CR |= RCC_CR_HSEON;            /*enable HSE clock*/
    while (!(RCC->CR&RCC_CR_HSERDY)){}   /*wait for HSE ready flag*/
    FLASH->ACR |= FLASH_ACR_PRFTBE;     /*enable prefetch buffer*/
    FLASH->ACR |= FLASH_ACR_LATENCY_1;  /*max delay for flash access when max clock frequency*/
    RCC->CFGR |= RCC_CFGR_PLLMULL9;      /*PLL multiplication factor is 9*/
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;     /*HSE is not devided for PLL*/
    RCC->CFGR |= RCC_CFGR_PLLSRC;       /*clock from HSE selected as PLL input clock*/
    RCC->CFGR &= ~RCC_CFGR_HPRE;        /*SYSCLK is not devided for HCLK (AHB)*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;   /*HCLK is devided by 2 for APB1 (36 MHz max)*/
    RCC->CFGR &= ~RCC_CFGR_PPRE2;       /*HCLK is not devided for APB2 (72 MHz max)*/
    RCC->CR |= RCC_CR_CSSON;/*enable CSS -> set CSSON*/
    RCC->CR |= RCC_CR_PLLON;/*enable PLL*/
    while (!(RCC->CR&RCC_CR_PLLRDY)){}/*wait for PLL ready flag*/
    RCC->CFGR |= RCC_CFGR_SW_PLL;       /*PLL is used as sys clock*/
    while (!(RCC->CFGR&RCC_CFGR_SWS_PLL)){}/*wait for PLL as SYSCLK clock flag*/
    SystemCoreClockUpdate();
}


/*
 * There is an interrupt every SYSCLOCK / times
 */
void systick_init(uint32_t times)
{
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk&(SystemCoreClock / times - 1);
    SysTick->VAL = SysTick_VAL_CURRENT_Msk;       /*reset counter*/
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk|\
                     SysTick_CTRL_TICKINT_Msk|\
                     SysTick_CTRL_ENABLE_Msk;
}


void delay(uint32_t tck)
{
    while(tck)
    {
        tck--;
    }  
}


// __STATIC_INLINE void delay_ms(uint32_t ms)
// {
//     SysTick->VAL = SysTick_VAL_CURRENT_Msk&(SYSCLOCK / ONE_MS - 1);    /*init counter*/
//     systick_cnt = ms;   /**/
//     while(systick_cnt){} /*wait for systick_cnt is inspired*/
// }


// __STATIC_INLINE void delay_us(uint32_t us)
// {
//     SysTick->VAL = SysTick_VAL_CURRENT_Msk&(SYSCLOCK / ONE_US - 1);    /*init counter*/
//     systick_cnt = us;   /**/
//     while(systick_cnt){} /*wait for systick_cnt is inspired*/
// }
