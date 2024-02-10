#include "arp.h"
#include "ip.h"
#include "icmp.h"
#include "udp.h"
#include "lan.h"

uint32_t ip_addr = IP_ADDR;
uint32_t ip_mask = IP_SUBNET_MASK;
uint32_t ip_gateway = IP_DEFAULT_GATEWAY;

/**
 * @brief Fills IP header when replying.
 *
 * @param packet IP header to fill.
 * @param len Total packet length.
 *
 */
static void fill_header(struct ip_packet *packet, uint16_t len);

uint16_t ip_cksum(uint32_t sum, uint8_t *buf, uint16_t len)
{
	while (len >= 2)
	{
		sum += ((uint16_t)*buf << 8) | *(buf+1);
		buf += 2;
		len -= 2;
	}

	if (len)
		sum += (uint16_t)*buf << 8;

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~htons((uint16_t)sum);
}

void ip_reply(struct eth_frame *frame, uint16_t len)
{
	struct ip_packet *packet = (struct ip_packet *)(frame->data);

    len += sizeof(struct ip_packet);
    fill_header(packet, len);
	eth_reply(frame, len);
}

void ip_filter(struct eth_frame *frame, uint16_t len)
{
    struct ip_packet *packet = (struct ip_packet*)(frame->data);
        
    if (len < sizeof(struct ip_packet))
        return;

    if( (packet->ver_head_len == 0x45) &&
        (packet->to_addr == ip_addr) )
    {
        len = ntohs(packet->total_len) - sizeof(struct ip_packet); /* date len */

        switch(packet->protocol) {
#ifdef WITH_ICMP
        case IP_PROTOCOL_ICMP:
            icmp_filter(frame, len);
            break;
#endif
        case IP_PROTOCOL_UDP:
            udp_filter(frame, len);
            break;
        }
    }
}

uint8_t ip_send(struct eth_frame *frame, uint16_t len)
{
    struct ip_packet *ip = (struct ip_packet *)(frame->data);
    uint32_t route_ip;
    uint8_t *mac_addr_to;

    // apply route
    if( ((ip->to_addr ^ ip_addr) & ip_mask) == 0 )
        route_ip = ip->to_addr;
    else
        route_ip = ip_gateway;

    // resolve mac address
    mac_addr_to = arp_resolve(route_ip);
    if(mac_addr_to == NULL)
        return 0;

    // send packet
    len += sizeof(ip_packet_t);

    memcpy(frame->to_addr, mac_addr_to, MAC_ADDR_LEN);
    frame->type = ETH_TYPE_IP;

    ip->ver_head_len = 0x45;
    ip->tos = 0;
    ip->total_len = htons(len);
    ip->fragment_id = 0;
    ip->flags_framgent_offset = 0;
    ip->ttl = IP_PACKET_TTL;
    ip->cksum = 0;
    ip->from_addr = ip_addr;
    ip->cksum = ip_cksum(0, (void*)ip, sizeof(ip_packet_t));
    
    eth_send(frame, len);
    return 1;
}

static void fill_header(struct ip_packet *packet, uint16_t len)
{
  	packet->total_len = htons(len);
	packet->fragment_id = 0;
	packet->flags_framgent_offset = 0;
	packet->ttl = IP_PACKET_TTL;
	packet->cksum = 0;
	packet->to_addr = packet->from_addr;
	packet->from_addr = ip_addr;
	packet->cksum = ip_cksum(0, (uint8_t *)packet, sizeof(struct ip_packet));
}

