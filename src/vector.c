#include <string.h>
#include "vector.h"
#include "ip.h"


static int
valid_vector(char *rawVector){
    //missing stuff
    return 0;
}

int
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
    newVector->protocol = parse_protocol(token[0]);
    newVector->srcIp = parse_ip(token[1]);
    newVector->srcPrt = parse_port(token[2]);
    newVector->dstIp = parse_ip(token[3]);
    newVector->dstPrt = parse_port(token[4]);
    strncpy(newVector->flags, token[5], strlen(token[5])+1);
    return 0; //success
}
