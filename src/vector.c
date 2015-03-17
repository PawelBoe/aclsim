#include <string.h>
#include "vector.h"
#include "ip.h"


static error_t
valid_vector(char *rawVector){
    //missing stuff
    return SUCCESS;
}

error_t
parse_vector(struct vector *newVector, char *rawVector, int lineNr){
    //missing validity checking
    valid_vector(rawVector);

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
    newVector->protocol = parse_protocol_ip(token[0]);
    newVector->srcIp = parse_address_ip(token[1]);
    newVector->srcPrt = parse_port_ip(token[2]);
    newVector->dstIp = parse_address_ip(token[3]);
    newVector->dstPrt = parse_port_ip(token[4]);
    strncpy(newVector->flags, token[5], strlen(token[5])+1);
    return SUCCESS;
}
