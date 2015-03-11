#ifndef VECTOR_H
#define VECTOR_H

#include "ip.h"
#include "constants.h"


int
valid_vector(char *rawVector);

struct vector{
    int number;
    int protocol;
    union ipAdr srcIp;
    union ipPort srcPrt;
    union ipAdr dstIp;
    union ipPort dstPrt;
    char flags[VECTORSIZE];
    char comment[VECTORSIZE];
};

void
parse_vector(struct vector *newVector, char *rawVector, int lineNr);

#endif
