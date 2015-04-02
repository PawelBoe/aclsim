//Copyright (C) Pawel Böning, 2015
#include <string.h>
#include "vector.h"


error_t
parse_vector(struct vector *newVector, char *rawVector, int *lineNr){
    error_t status = SUCCESS;
    int i;
    char *token[6];
    char buff[VECTORSIZE];
    strncpy(buff, rawVector, VECTORSIZE);
    buff[VECTORSIZE-1] = '\0';

    for(i = 0; i < 6; i++){ //initialize tokens (no NULL-Ptr!)
        token[i] = "";
    }

    token[0] = strtok(buff, " \n");
    for (i = 1; i < 6 && token[i-1] != NULL; i++){
        token[i] = strtok(NULL, " \n");
    }
    if (token[i-1] == NULL){
        token[i-1] = ""; //no NULL-Ptr!
    }

    newVector->number = *lineNr;
    (*lineNr)++;
    status |= parse_protocol_ip(&newVector->protocol, token[0]);
    status |= parse_address_ip(&newVector->srcAdr, token[1]);
    status |= parse_port_ip(&newVector->srcPrt, token[2]);
    status |= parse_address_ip(&newVector->dstAdr, token[3]);
    status |= parse_port_ip(&newVector->dstPrt, token[4]);
    strncpy(newVector->flags, token[5], strlen(token[5])+1);

    return status;
}

error_t
string_vector(char *newString, struct vector *oldVector){
    error_t status = SUCCESS;
    char tmp[VECTORSIZE] = "";

    status |= string_protocol(tmp, oldVector->protocol);
    strncat(newString, tmp, strlen(tmp)+1);
    strncat(newString, " ", 2);

    status |= string_address(tmp, oldVector->srcAdr);
    strncat(newString, tmp, strlen(tmp)+1);
    strncat(newString, " ", 2);

    status |= string_port(tmp, oldVector->srcPrt);
    strncat(newString, tmp, strlen(tmp)+1);
    strncat(newString, " ", 2);

    status |= string_address(tmp, oldVector->dstAdr);
    strncat(newString, tmp, strlen(tmp)+1);
    strncat(newString, " ", 2);

    status |= string_port(tmp, oldVector->dstPrt);
    strncat(newString, tmp, strlen(tmp)+1);

    return status;
}
