#include <string.h>
#include <stdlib.h>
#include "rule.h"
#include "ip.h"


static error_t
parse_action_rule(int * newAction, char *rawAction){
    error_t status = SUCCESS;

    if (strncmp(rawAction, "deny", 4) == 0){
        *newAction = AC_DENY;
    }
    else if (strncmp(rawAction, "permit", 6) == 0) {
        *newAction = AC_PERMIT;
    }
    else if (strncmp(rawAction, "remark", 6) == 0) {
        *newAction = AC_REMARK;
    }
    else{
        *newAction = AC_UNKNOWN;
        status = ERR_GENERIC;
    }

    return status;
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
        parse_address_ip(startAdr, token[*tokensExtracted + 1]);
        *endAdr = *startAdr;
        *tokensExtracted += 2;
    }
    else{
        parse_address_ip(startAdr, token[*tokensExtracted]);
        parse_address_ip(endAdr, token[*tokensExtracted + 1]);
        transform_wildcard_ip(startAdr, endAdr);
        *tokensExtracted += 2;
    }

    return SUCCESS;
}

static error_t
parse_port_rule(char *token[], union ipPrt *startPrt, union ipPrt *endPrt,
        int *prtNeg, int *tokensExtracted){
    if(strncmp(token[*tokensExtracted], "eq", 2) == 0){
        parse_port_ip(startPrt, token[*tokensExtracted + 1]);
        *endPrt = *startPrt;
        *prtNeg = 0;
        *tokensExtracted += 2;
    }
    else if (strncmp(token[*tokensExtracted], "neq", 3) == 0){
        parse_port_ip(startPrt, token[*tokensExtracted + 1]);
        *endPrt = *startPrt;
        *prtNeg = 1;
        *tokensExtracted += 2;
    }
    else if (strncmp(token[*tokensExtracted], "gt", 2) == 0){
        parse_port_ip(startPrt, token[*tokensExtracted + 1]);
        endPrt->value = 0xFFFF;
        *prtNeg = 0;
        *tokensExtracted += 2;
    }
    else if (strncmp(token[*tokensExtracted], "lt", 2) == 0){
        startPrt->value = 0x0000;
        parse_port_ip(endPrt, token[*tokensExtracted + 1]);
        *prtNeg = 0;
        *tokensExtracted += 2;
    }
    else if (strncmp(token[*tokensExtracted], "range", 5) == 0){
        parse_port_ip(startPrt, token[*tokensExtracted + 1]);
        parse_port_ip(endPrt, token[*tokensExtracted + 2]);
        *prtNeg = 0;
        *tokensExtracted += 3;
    }
    else {
        startPrt->value = 0x0000;
        endPrt->value = 0xFFFF;
        *prtNeg = 0;
    }

    return SUCCESS;
}

error_t
parse_rule(struct rule *newRule, char *rawRule, int *lineNr){
    error_t status = SUCCESS;
    int i;
    char *token[12];
    char buff[RULESIZE];
    strncpy(buff, rawRule, RULESIZE);
    buff[RULESIZE-1] = '\0';

    int tokensExtracted = 0;

    for(i = 0; i < 12; i++){ //initialize tokens (no NULL-Ptr!)
        token[i] = "";
    }

    token[0] = strtok(buff, " ");
    for (i = 1; i < 12 && token[i-1] != NULL; i++){
        token[i] = strtok(NULL, " ");
    }
    if (token[i-1] == NULL){
        token[i-1] = ""; //no NULL-Ptr!
    }

    newRule->number = *lineNr;

    status |= parse_action_rule(&newRule->action, token[0]);
    tokensExtracted++;
    //only count if a rule was parsed
    if (newRule->action == AC_DENY || newRule->action == AC_PERMIT){
        (*lineNr)++;
    }

    status |= parse_protocol_ip(&newRule->protocol, token[1]);
    tokensExtracted++;

    status |= parse_address_rule(token, &newRule->srcIpStart,
            &newRule->srcIpEnd, &tokensExtracted);

    status |= parse_port_rule(token, &newRule->srcPrtStart,
            &newRule->srcPrtEnd, &newRule->srcPrtNeg, &tokensExtracted);

    status |= parse_address_rule(token, &newRule->dstIpStart,
            &newRule->dstIpEnd, &tokensExtracted);

    status |= parse_port_rule(token, &newRule->dstPrtStart,
            &newRule->dstPrtEnd, &newRule->dstPrtNeg, &tokensExtracted);

    return status;
}
