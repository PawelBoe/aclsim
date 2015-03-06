#include <stdlib.h>
#include "ip.h"


union ipAdr
parse_ip(char *rawIp){
    int i, j;
    union ipAdr newAddtess;
    char token[4][BUFSIZE] = {};

    for(i = 0; i < 4; i++){
        for(j = 0; *rawIp != '.' && *rawIp != '\0' && j < BUFSIZE-1; j++){
            token[i][j] = *rawIp;
            rawIp++;
        }
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
    //missing stuff
    return 0;
}
