#include <avr/io.h>
#include "lan.h"
#include "buart.h"

int main()
{
	lan_init();
	uart_init();
	sei();

	while(1)
		lan_poll();

	return 0;
}
