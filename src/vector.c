#include <stdlib.h>
#include <string.h>
#include "vector.h"


union ipAdr
parseIp(char *rawIp){
	union ipAdr address;
	//stuff missing
	return address;
}

union ipPort
parsePort(char *rawPort){
	union ipPort port;
	// stuff missing
	return port;
}

int
valid_vector(char rawVector[VECTORSIZE]){
	//Valid format: xxx.xxx.xxx.xxx xxxxx xxx.xxx.xxx.xxx xxxxx FLAGS COMMENT
	// xxx: 000 - 255
	// xxxxx: 00000 - 65535
	return 0;
}

struct vector
parse_vector(char rawVector[VECTORSIZE], int lineNr){
	int j;
	int i;
	struct vector newVector;
	char token[7][VECTORSIZE/2];

	//Fehlerhafte zuweisung von random fragmenten
	for(i = 0, j = 0; rawVector[j] == '\0'; j++){
		if(rawVector[j] == ' '){
			i++;
			continue;
		}
		token[i][j] = rawVector[j];
	}

	newVector.number = lineNr;
	strncpy(newVector.protocol, token[0], strlen(token[0]));
	newVector.srcIp = parseIp(token[1]);
	newVector.srcPrt = parsePort(token[2]);
	newVector.dstIp = parseIp(token[3]);
	newVector.dstPrt = parsePort(token[4]);
	strncpy(newVector.flags, token[5], strlen(token[5]));
	strncpy(newVector.comment, token[6], strlen(token[6]));
	return newVector;
}
