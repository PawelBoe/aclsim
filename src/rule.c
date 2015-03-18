#include <string.h>
#include <stdlib.h>
#include "rule.h"
#include "ip.h"


static error_t
valid_rule(char *rawRule){
    //missing stuff
    return SUCCESS;
}

static int
parse_action_rule(char *rawAction){
    int newAction;
    if (strncmp(rawAction, "deny", 4) == 0){
        newAction = AC_DENY;
    }
    else if (strncmp(rawAction, "permit", 6) == 0) {
        newAction = AC_PERMIT;
    }
    else if (strncmp(rawAction, "remark", 6) == 0) {
        newAction = AC_REMARK;
    }
    else{
        newAction = AC_UNKNOWN;
    }

    return newAction;
}

static error_t
parse_address_rule(char *token[], union ipAdr *startAdr, union ipAdr *endAdr,
        int *tokensExtracted){
    if(strncmp(token[*tokensExtracted], "any", 3) == 0){
        startAdr->value = 0x00000000;
        endAdr->value = 0xFFFFFFFF;
        *tokensExtracted += 1;
    }
    else if (strncmp(token[*tokensExtracted], "host", 4) == 0){
        *startAdr = parse_address_ip(token[*tokensExtracted + 1]);
        *endAdr = *startAdr;
        *tokensExtracted += 2;
    }
    else{
        *startAdr = parse_address_ip(token[*tokensExtracted]);
        *endAdr = parse_address_ip(token[*tokensExtracted + 1]);
        transform_wildcard_ip(startAdr, endAdr);
        *tokensExtracted += 2;
    }

    return SUCCESS;
}

static error_t
parse_port_rule(char *token[], union ipPrt *startPrt, union ipPrt *endPrt,
        int *tokensExtracted){
    if(strncmp(token[*tokensExtracted], "eq", 2) == 0){
        *startPrt = parse_port_ip(token[*tokensExtracted + 1]);
        *endPrt = *startPrt;
        *tokensExtracted += 2;
    }
    else if (strncmp(token[*tokensExtracted], "gt", 2) == 0){
        *startPrt = parse_port_ip(token[*tokensExtracted + 1]);
        endPrt->value = 0xFFFF;
        *tokensExtracted += 2;
    }
    else if (strncmp(token[*tokensExtracted], "lt", 2) == 0){
        startPrt->value = 0x0000;
        *endPrt = parse_port_ip(token[*tokensExtracted + 1]);
        *tokensExtracted += 2;
    }
    else if (strncmp(token[*tokensExtracted], "range", 5) == 0){
        *startPrt = parse_port_ip(token[*tokensExtracted + 1]);
        *endPrt = parse_port_ip(token[*tokensExtracted + 2]);
        *tokensExtracted += 3;
    }
    else {
        startPrt->value = 0x0000;
        endPrt->value = 0xFFFF;
    }

    return SUCCESS;
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

    union ipAdr startAdr;
    union ipAdr endAdr;
    union ipPrt startPrt;
    union ipPrt endPrt;
    int tokensExtracted = 0;

    for(i = 0; i < 12; i++){ //initialize tokens (no NULL-Ptr!)
        token[i] = "";
    }

    token[0] = strtok(buff, " ");
    for (i = 1; i < 12 && token[i-1] != NULL; i++){
        token[i] = strtok(NULL, " ");
    }
    token[i-1] = ""; //no NULL-Ptr!

    newRule->number = lineNr;

    newRule->action = parse_action_rule(token[0]);
    tokensExtracted++;

    newRule->protocol = parse_protocol_ip(token[1]);
    tokensExtracted++;

    parse_address_rule(token, &startAdr, &endAdr, &tokensExtracted);
    newRule->srcIpStart = startAdr;
    newRule->srcIpEnd = endAdr;

    parse_port_rule(token, &startPrt, &endPrt, &tokensExtracted);
    newRule->srcPrtStart = startPrt;
    newRule->srcPrtEnd = endPrt;

    parse_address_rule(token, &startAdr, &endAdr, &tokensExtracted);
    newRule->dstIpStart = startAdr;
    newRule->dstIpEnd = endAdr;

    parse_port_rule(token, &startPrt, &endPrt, &tokensExtracted);
    newRule->dstPrtStart = startPrt;
    newRule->dstPrtEnd = endPrt;

    return SUCCESS;
}
