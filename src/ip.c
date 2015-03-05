#include <stdlib.h>
#include "ip.h"


union ipAdr
parseIp(char *rawIp){
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
parsePort(char *rawPort){
	union ipPort newPort;
	newPort.value = atoi(rawPort);
	return newPort;
}

int
parseProtocol(char *rawProtocol){
	//missing stuff
	return 0;
}
