//Copyright (C) Pawel Böning, 2015
#ifndef IP_H
#define IP_H

#include <stdint.h>
#include "constants.h"


union ipAdr{
    uint8_t byte[4] ;
    uint32_t value;
};

union ipPrt{
    uint8_t byte[2];
    uint16_t value;
};

extern error_t
parse_address_ip(union ipAdr *newAddress, const char *rawIp);

extern error_t
parse_port_ip(union ipPrt *newPort, const char *rawPort);

extern error_t
parse_protocol_ip(int *newProtocol, const char *rawProtocol);

extern void
transform_wildcard_ip(union ipAdr *address, union ipAdr *wildcard);

#endif
