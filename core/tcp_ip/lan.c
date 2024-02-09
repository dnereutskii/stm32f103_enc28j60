#include "enc28j60.h"
#include "ethernet.h"
#include "lan.h"

uint8_t net_buf[ENC28J60_MAXFRAME];

void lan_init(void)
{
	enc28j60_init(mac_addr);
}

void lan_poll(void)
{
	struct eth_frame *frame = (struct eth_frame *)net_buf;
	
	uint16_t len = enc28j60_recv_packet(net_buf, sizeof(net_buf));
	eth_filter(frame, len);
}
