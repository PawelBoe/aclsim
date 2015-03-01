#ifndef VECTOR_H
#define VECTOR_H

#include "ip.h"
#define VECTORSIZE 128


//Hint: chars are guaranteed to be 8 bits long
//IPv4 addresses are 4 bytes long
//IPv4 ports are 2 bytes long

int
valid_vector(char *rawVector);

struct vector{
	int number;
	char protocol[VECTORSIZE];
	union ipAdr srcIp;
	union ipPort srcPrt;
	union ipAdr dstIp;
	union ipPort dstPrt;
	char flags[VECTORSIZE];
	char comment[VECTORSIZE];
};

struct vector
parse_vector(char *rawVector, int lineNr);

#endif
