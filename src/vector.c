#include <string.h>
#include "vector.h"
#include "ip.h"


int
valid_vector(char *rawVector){
    //missing stuff
    return 0;
}

struct vector
parse_vector(char *rawVector, int lineNr){
    int i, j;
    struct vector newVector;
    char token[7][VECTORSIZE] = {};

    for(i = 0; i < 7; i++){
        for(j = 0; *rawVector != ' ' && *rawVector != '\0' && j < VECTORSIZE-1; j++){
            token[i][j] = *rawVector;
            rawVector++;
        }
        rawVector++;
    }
    newVector.number = lineNr;
    newVector.protocol = parse_protocol(token[0]);
    newVector.srcIp = parse_ip(token[1]);
    newVector.srcPrt = parse_port(token[2]);
    newVector.dstIp = parse_ip(token[3]);
    newVector.dstPrt = parse_port(token[4]);
    strncpy(newVector.flags, token[5], strlen(token[5]));
    strncpy(newVector.comment, token[6], strlen(token[6]));
    return newVector;
}
