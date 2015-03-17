#include <string.h>
#include <stdio.h>
#include "rule.h"
#include "ip.h"
#include "constants.h"


void
skipLine(FILE *stream){
    while(getc(stream) != '\n');
}

int
main(int argc, char *argv[])
{
    struct rule TEST;
    char STRING[VECTORSIZE];
    int number = 0;
    while(fgets(STRING, VECTORSIZE-1, stdin)) {
        if(STRING[strlen(STRING)-1] != '\n')
            skipLine(stdin);
        parse_rule(&TEST, STRING, number);
        printf("|%d|%d|%d|%d %d %d %d|%d %d %d %d|%d %d %d %d|%d %d %d %d|%d|%d|%d|%d\n",

        TEST.number, TEST.action, TEST.protocol,

        TEST.srcIpStart.byte[0], TEST.srcIpStart.byte[1], TEST.srcIpStart.byte[2], TEST.srcIpStart.byte[3],
        TEST.srcIpEnd.byte[0], TEST.srcIpEnd.byte[1], TEST.srcIpEnd.byte[2], TEST.srcIpEnd.byte[3],

        TEST.dstIpStart.byte[0], TEST.dstIpStart.byte[1], TEST.dstIpStart.byte[2], TEST.dstIpStart.byte[3],
        TEST.dstIpEnd.byte[0], TEST.dstIpEnd.byte[1], TEST.dstIpEnd.byte[2], TEST.dstIpEnd.byte[3],

        TEST.srcPrtStart.value,
        TEST.srcPrtEnd.value,

        TEST.dstPrtStart.value,
        TEST.dstPrtEnd.value
        );

        number++;
    }
    return 0;
}
