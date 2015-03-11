#include <string.h>
#include <stdio.h>
#include "vector.h"
#include "ip.h"
#include "constants.h"

void
parse_vectorTest(struct vector *newVector, char *rawVector, int lineNr){
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
}

void skipLine(FILE *stream){
    while(getc(stream) != '\n');
}

int main(int argc, char *argv[])
{
    struct vector TEST;
    char STRING[VECTORSIZE];
    int number = 0;
    while(fgets(STRING, VECTORSIZE-1, stdin)) {
        if(STRING[strlen(STRING)-1] != '\n')
            skipLine(stdin);
        parse_vectorTest(&TEST, STRING, number);
        printf("|%d|%u|%u %u %u %u|%u|%u %u %u %u|%u|%s|\n", TEST.number, TEST.protocol,
        TEST.srcIp.byte[0], TEST.srcIp.byte[1], TEST.srcIp.byte[2], TEST.srcIp.byte[3], TEST.srcPrt.value,
        TEST.dstIp.byte[0], TEST.dstIp.byte[1], TEST.dstIp.byte[2], TEST.dstIp.byte[3], TEST.dstPrt.value,
        TEST.flags);
        number++;
    }
    return 0;
}
