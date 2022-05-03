#ifndef __INDICATOR_H
#define __INDICATOR_H

#include <stm32f1xx.h>

void indicator_init();
void indicator_print_number(uint16_t number);
void indicator_update();


#endif /*__INDICATOR_H*/