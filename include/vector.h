//Copyright (C) Pawel Böning, 2015
#ifndef VECTOR_H
#define VECTOR_H

#include "ip.h"
#include "constants.h"


struct vector{
    int number;
    int protocol;
    union ipAdr srcAdr;
    union ipPrt srcPrt;
    union ipAdr dstAdr;
    union ipPrt dstPrt;
    char flags[VECTORSIZE];
};

extern error_t
parse_vector(struct vector *newVector, char *rawVector, int *lineNr);

extern error_t
string_vector(char *newString, struct vector *oldVector);
#endif
