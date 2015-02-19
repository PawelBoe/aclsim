#ifndef VECTOR_H
#define VECTOR_H

#define VECTORSIZE 128


//Hint: chars are guaranteed to be 8 bits long
//IPv4 addresses are 4 bytes long
//IPv4 ports are 2 bytes long

typedef unsigned char byte_t;

union ipAdr{
	byte_t byte[4] ;
	unsigned int value;
};

union ipPort{
	byte_t byte[2];
	unsigned int value;
};

int
valid_vector(char rawVector[VECTORSIZE]);

struct vector{
	int number;
	char protocol[VECTORSIZE/16];
	union ipAdr srcIp;
	union ipPort srcPrt;
	union ipAdr dstIp;
	union ipPort dstPrt;
	char flags[VECTORSIZE/16];
	char comment[VECTORSIZE/2];
};

union ipAdr
parseIp(char *rawIp);


union ipPort
parsePort(char *rawPort);

struct vector
parse_vector(char*, int);

#endif
