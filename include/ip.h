#ifndef IP_H
#define IP_H

#define BUFSIZE 128

typedef unsigned char byte_t;

union ipAdr{
	byte_t byte[4] ;
	unsigned int value;
};

union ipPort{
	byte_t byte[2];
	unsigned int value;
};

union ipAdr
parseIp(char *rawIp);

union ipPort
parsePort(char *rawPort);

#endif
