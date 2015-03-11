#include <string.h>
#include "vector.h"
#include "ip.h"


int
valid_vector(char *rawVector){
    //missing stuff
    return 0;
}

void
parse_vector(struct vector *newVector, char *rawVector, int lineNr){
    int i;
    char *token[6];
    char buff[VECTORSIZE];
    strncpy(buff, rawVector, VECTORSIZE);
    buff[VECTORSIZE-1] = '\0';

    token[0] = strtok(buff, " \n");
    for (i = 1; i < 6; i++){
        token[i] = strtok(NULL, " \n");
    }

    newVector->number = lineNr;
    newVector->protocol = parse_protocol(token[0]);
    newVector->srcIp = parse_ip(token[1]);
    newVector->srcPrt = parse_port(token[2]);
    newVector->dstIp = parse_ip(token[3]);
    newVector->dstPrt = parse_port(token[4]);
    strncpy(newVector->flags, token[5], strlen(token[5])+1);
}
