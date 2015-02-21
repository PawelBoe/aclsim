#include <stdlib.h>
#include "ip.h"


union ipAdr
parseIp(char *rawIp){
	int i, j;
	union ipAdr address;
	char token[4][BUFSIZE] = {};

	for(i = 0; i < 4; i++){
		for(j = 0; *rawIp != '.' && *rawIp != '\0' && j < BUFSIZE-1; j++){
			token[i][j] = *rawIp;
			rawIp++;
		}
		rawIp++;
	}
	for(i = 0; i < 4; i++){
		address.byte[i] = atoi(token[i]);
	}
	return address;
}

union ipPort
parsePort(char *rawPort){
	union ipPort port;
	port.value = atoi(rawPort);
	return port;
}
