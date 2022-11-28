#ifndef LAN_H
#define LAN_H

/*
 * Config
 */

#define WITH_ICMP

#define MAC_ADDR            {0x00,0x80,0xE1,0x00,0x00,0x00}
#define IP_ADDR	            inet_addr(192, 168, 0, 222)

#define IP_PACKET_TTL       64


void lan_init();
void lan_poll();


#endif /*LAN_H*/