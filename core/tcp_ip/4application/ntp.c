#include "ip.h"
#include "udp.h"
#include "ntp.h"

uint8_t ntp_request(uint32_t srv_ip)
{
    struct eth_frame *frame = (struct eth_frame *)net_buf;
    struct ip_packet *ip = (struct ip_packet *)(frame->data);
    struct udp_packet *udp = (struct udp_packet *)(ip->data);
    struct ntp_message *ntp = (struct ntp_message *)(udp->data);

    ip->to_addr = srv_ip;
    udp->to_port = NTP_SRV_PORT;
    udp->from_port = NTP_LOCAL_PORT;

    memset(ntp, 0, sizeof(struct ntp_message));
    ntp->status = 0x08;

    return udp_send(frame, sizeof(struct ntp_message));
}

uint32_t ntp_parse_reply(void *data, uint16_t len)
{
    struct ntp_message *ntp = data;
    uint32_t temp;

    if(len >= sizeof(struct ntp_message)) {
        temp = ntp->xmit_timestamp.seconds;
        return (ntohl(temp) - 2208988800UL);
    }
    return 0;
}

