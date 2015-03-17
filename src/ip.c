#include <stdlib.h>
#include <string.h>
#include "ip.h"


union ipAdr
parse_address_ip(char *rawIp){
    int i;
    char *token[4];
    char buff[IPSIZE];
    strncpy(buff, rawIp, IPSIZE);
    buff[IPSIZE-1] = '\0';
    union ipAdr newAddtess;

    token[0] = strtok(buff, ".");
    for(i = 1; i < 4; i++){
        token[i] = strtok(NULL, ".");
    }

    for(i = 0; i < 4; i++){
        newAddtess.byte[i] = atoi(token[i]);
    }

    return newAddtess;
}

union ipPort
parse_port_ip(char *rawPort){
    union ipPort newPort;
    newPort.value = atoi(rawPort);
    return newPort;
}

int
parse_protocol_ip(char *rawProtocol){
    int newProtocol;
    if (strncmp(rawProtocol, "tcp", 3) == 0){
       newProtocol = PROTO_TCP;
    }
    else if(strncmp(rawProtocol, "udp", 3) == 0){
        newProtocol = PROTO_UDP;
    }
    else if(strncmp(rawProtocol, "esp", 3) == 0){
        newProtocol = PROTO_ESP;
    }
    else if(strncmp(rawProtocol, "icmp", 4) == 0){
        newProtocol = PROTO_ICMP;
    }
    else if(strncmp(rawProtocol, "ip", 2) == 0){
        newProtocol = PROTO_IP;
    }
    else{
        newProtocol = PROTO_UNKNOWN;
    }

    return newProtocol;
}

void
transform_wildcard_ip(union ipAdr *address, union ipAdr *wildcard){
    int i;
    union ipAdr tmp;

    for (i = 0; i < 4; i++){
        tmp.byte[i] = address->byte[i] &~ wildcard->byte[i];
    }
    *address = tmp;

    for (i = 0; i < 4; i++){
        tmp.byte[i] = address->byte[i] | wildcard->byte[i];
    }
    *wildcard = tmp;
}
