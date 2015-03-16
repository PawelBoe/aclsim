#ifndef IP_H
#define IP_H

#include <stdint.h>
#include "constants.h"


union ipAdr{
    uint8_t byte[4] ;
    uint32_t value;
};

union ipPort{
    uint8_t byte[2];
    uint16_t value;
};

extern union ipAdr
parse_address_ip(char *rawIp);

extern union ipPort
parse_port_ip(char *rawPort);

extern int
parse_protocol_ip(char *rawProtocol);

#endif
