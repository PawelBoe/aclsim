#include <string.h>
#include "vector.h"
#include "ip.h"


int
valid_vector(char *rawVector){
	//Valid format: PROTOCOL xxx.xxx.xxx.xxx xxxxx xxx.xxx.xxx.xxx xxxxx FLAGS COMMENT
	// xxx: 000 - 255
	// xxxxx: 00000 - 65535
/*
	if(mainToken == 7)
	if(subToken == 4)
	if(x <= 255 && x >= 0)
	if(x <= 65535 && x >= 0)

	if(f <= 8 && f >= 0) 
*/
	return 0;
}

struct vector
parse_vector(char *rawVector, int lineNr){
	int i, j;
	struct vector newVector;
	char token[7][VECTORSIZE] = {};

	for(i = 0; i < 7; i++){
		for(j = 0; *rawVector != ' ' && *rawVector != '\0' && j < VECTORSIZE-1; j++){
			token[i][j] = *rawVector;
			rawVector++;
		}
		rawVector++;
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
