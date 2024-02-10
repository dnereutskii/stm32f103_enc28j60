#ifndef NTP_H
#define NTP_H

#include <stdint.h>
#include "ethernet.h"

#define NTP_SRV_PORT		htons(123)
#define NTP_LOCAL_PORT		htons(14444)

#pragma pack(push, 1)
struct ntp_timestamp {
	uint32_t seconds;
	uint32_t fraction;
};

struct ntp_message {
    uint8_t status;
    uint8_t type;
    uint16_t precision;
    uint32_t est_error;
    uint32_t est_drift_rate;
    uint32_t ref_clock_id;
    struct ntp_timestamp ref_timestamp;
    struct ntp_timestamp orig_timestamp;
    struct ntp_timestamp recv_timestamp;
    struct ntp_timestamp xmit_timestamp;
};
#pragma pack(pop)


uint8_t ntp_request(uint32_t srv_ip);
uint32_t ntp_parse_reply(void *data, uint16_t len);

#endif /* NTP_H */
