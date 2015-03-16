#include <string.h>
#include "rule.h"
#include "ip.h"


static int
valid_rule(char *rawRule){
    //missing stuff
    return 0;
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

static int
parse_address_rule(char *token[], union ipAdr *startAdr, union ipAdr *endAdr,
        int *tokensExtracted){
    //missing stuff
    return 0;
}

static int
parse_port_rule(char *token[], union ipPort *startPrt, union ipPort *endPrt,
        int *tokensExtracted){
    //missing stuff
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

    union ipAdr startAdr;
    union ipAdr endAdr;
    union ipPort startPrt;
    union ipPort endPrt;
    int tokensExtracted = 0;

    token[0] = strtok(buff, " ");
    for (i = 1; i < 12; i++){
        token[i] = strtok(NULL, " ");
    }

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
