#include <string.h>
#include <stdio.h>
#include "vector.h"
#include "ip.h"

struct vector
parse_vector(char *rawVector, int lineNr){
    int x;
    char *token[7];
    struct vector newVector;
    char buff[100];
    strncpy(buff, rawVector, strlen(rawVector)+1);

    token[0] = strtok(buff, " ");
    for (x = 1; x < 7; x++){
        token[x] = strtok(NULL, " ");
    }
    printf("token0: %s\n",token[0]);
    printf("token1: %s\n",token[1]);
    printf("token2: %s\n",token[2]);
    printf("token3: %s\n",token[3]);
    printf("token4: %s\n",token[4]);
    printf("token5: %s\n",token[5]);
    printf("token6: %s\n",token[6]);

    newVector.number = lineNr;
    newVector.protocol = parse_protocol(token[0]);
    newVector.srcIp = parse_ip(token[1]);
    newVector.srcPrt = parse_port(token[2]);
    newVector.dstIp = parse_ip(token[3]);
    newVector.dstPrt = parse_port(token[4]);
    strncpy(newVector.flags, token[5], strlen(token[5])+1);
    strncpy(newVector.comment, token[6], strlen(token[6])+1);
    return newVector;
}

struct vector
parse_vectorTwo(char *rawVector, int lineNr){
    int i, j;
    struct vector newVector;
    char token[7][VECTORSIZE] = {};

    for(i = 0; i < 7; i++){
        for(j = 0; *rawVector != ' ' && *rawVector != '\0' && j < VECTORSIZE-1; j++){
            token[i][j] = *rawVector;
            rawVector++;
        }
        //insert \0 character after last j++?
        token[i][j] = '\0';
        rawVector++;
    }

    newVector.number = lineNr;
    newVector.protocol = parse_protocol(token[0]);
    newVector.srcIp = parse_ip(token[1]);
    newVector.srcPrt = parse_port(token[2]);
    newVector.dstIp = parse_ip(token[3]);
    newVector.dstPrt = parse_port(token[4]);
    strncpy(newVector.flags, token[5], strlen(token[5])+1);
    strncpy(newVector.comment, token[6], strlen(token[6])+1);
    return newVector;
}
int main(int argc, char *argv[])
{
    struct vector TEST = {};
    char *STRING = "udp 123.121.123.121 12345 121.123.121.123 54321 FLAGS COMMENT";
    TEST = parse_vector(STRING, 1);
	printf("|%d|%u|%u %u %u %u|%u|%u %u %u %u|%u| %s | %s |\n", TEST.number, TEST.protocol,
	TEST.srcIp.byte[0], TEST.srcIp.byte[1], TEST.srcIp.byte[2], TEST.srcIp.byte[3], TEST.srcPrt.value,
	TEST.dstIp.byte[0], TEST.dstIp.byte[1], TEST.dstIp.byte[2], TEST.dstIp.byte[3], TEST.dstPrt.value,
	TEST.flags, TEST.comment);
    return 0;
}
