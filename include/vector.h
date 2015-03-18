#ifndef VECTOR_H
#define VECTOR_H

#include "ip.h"
#include "constants.h"


struct vector{
    int number;
    int protocol;
    union ipAdr srcIp;
    union ipPrt srcPrt;
    union ipAdr dstIp;
    union ipPrt dstPrt;
    char flags[VECTORSIZE];
};

extern error_t
parse_vector(struct vector *newVector, char *rawVector, int lineNr);

#endif
