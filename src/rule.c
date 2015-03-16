#include <string.h>
#include "rule.h"
#include "ip.h"


static int
valid_rule(char *rawRule){
    //missing stuff
    return 0;
}

static int
parse_action(char *rawAction){
    //missing stuff
    return 0;
}

static int
parse_address(char *tok1[], union ipAdr addr, union ipAdr wild, unsigned int *charsExtracted){

    return 0;
}

error_t
parse_rule(struct rule *newRule, char *rawRule, int lineNr){
    //missing validity checking
    valid_rule(rawRule);

    int i;
    char *token[12];
    char buff[RULESIZE];
    strncpy(buff, rawRule, RULESIZE);
    buff[RULESIZE-1] = '\0';

    union ipAdr addr;
    union ipAdr wild;
    unsigned int *tokensExtracted = 0;

    newRule->number = lineNr;

    token[0] = strtok(buff, " "); //action
    newRule->action = parse_action(token[0]);
    tokensExtracted++;

    token[1] = strtok(NULL, " "); //protocol
    newRule->protocol = parse_protocol(token[1]);
    tokensExtracted++;

    for (i = 2; i < 12; ++i){
        token[i] = strtok(NULL, " ");
    }

    parse_address(token, addr, wild, tokensExtracted);
    //missing stuff


    return SUCCESS;
}

