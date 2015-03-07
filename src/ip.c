#include <stdlib.h>
#include <string.h>
#include "ip.h"


union ipAdr
parse_ip(char *rawIp){
    int i, j;
    union ipAdr newAddtess;
    char token[4][4] = {};

    for(i = 0; i < 4; i++){
        for(j = 0; *rawIp != '.' && *rawIp != '\0' && j < 3; j++){
            token[i][j] = *rawIp;
            rawIp++;
        }
        token[i][j] = '\0';
        rawIp++;
    }
    for(i = 0; i < 4; i++){
        newAddtess.byte[i] = atoi(token[i]);
    }
    return newAddtess;
}

union ipPort
parse_port(char *rawPort){
    union ipPort newPort;
    newPort.value = atoi(rawPort);
    return newPort;
}

int
parse_protocol(char *rawProtocol){
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
