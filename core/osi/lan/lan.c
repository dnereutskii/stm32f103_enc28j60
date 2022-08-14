#include "lan.h"


uint8_t net_buf[ENC28J60_MAXFRAME];


void lan_init()
{
	enc28j60_init(mac_addr);
}


void lan_poll()
{
	uint16_t len;
	eth_frame_t *frame = (void*)net_buf;
	
	while((len = enc28j60_recv_packet(net_buf, sizeof(net_buf))))
		eth_filter(frame, len);
}