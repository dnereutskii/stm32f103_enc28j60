#include <avr/io.h>
#include "lan.h"
#include "buart.h"

void udp_packet(eth_frame_t *frame, uint16_t len)
{
	ip_packet_t *ip = (void*)(frame->data);
	udp_packet_t *udp = (void*)(ip->data);
	uint8_t *data = udp->data;
	uint8_t i, count;

	for(i = 0; i < len; ++i)
		uart_write(data[i]);

	count = uart_rx_count();
	if(count)
	{
		for(i = 0; i < count; ++i)
			data[i] = uart_read();
		udp_reply(frame, count);
	}
}

int main()
{
	lan_init();
	uart_init();
	sei();

	while(1)
		lan_poll();

	return 0;
}
