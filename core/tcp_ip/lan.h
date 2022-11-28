#ifndef LAN_H
#define LAN_H

/*
 * Config
 */

#define WITH_ICMP

#define MAC_ADDR            {0x00,0x13,0x37,0x01,0x23,0x45}
#define IP_ADDR	            inet_addr(192, 168, 0, 222)

#define IP_PACKET_TTL       64


void lan_init();
void lan_poll();


#endif /*LAN_H*/