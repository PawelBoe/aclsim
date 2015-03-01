#ifndef IP_H
#define IP_H

#include <stdint.h>
#define BUFSIZE 128


union ipAdr{
	uint8_t byte[4] ;
	uint32_t value;
};

union ipPort{
	uint8_t byte[2];
	uint16_t value;
};

union ipAdr
parseIp(char *rawIp);

union ipPort
parsePort(char *rawPort);

#endif
