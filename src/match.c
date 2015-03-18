#include <stdio.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


error_t
check_match(struct match *newMatch, struct vector *vector, struct rule *rule){
    newMatch->vectorNr = vector->number;
    newMatch->ruleNr = rule->number;

    if (rule->action == AC_REMARK){
        newMatch->state = ST_REMARK;
    }
    else if (vector->protocol != rule->protocol && rule->protocol != PROTO_IP){
        newMatch->state = ST_NOMATCH;
    }

    else if(!(vector->srcIp.byte[0] >= rule->srcIpStart.byte[0]) ||
            !(vector->srcIp.byte[0] <= rule->srcIpEnd.byte[0])){
                newMatch->state = ST_NOMATCH;
    }
    else if(!(vector->srcIp.byte[1] >= rule->srcIpStart.byte[1]) ||
            !(vector->srcIp.byte[1] <= rule->srcIpEnd.byte[1])){
                newMatch->state = ST_NOMATCH;
    }
    else if(!(vector->srcIp.byte[2] >= rule->srcIpStart.byte[2]) ||
            !(vector->srcIp.byte[2] <= rule->srcIpEnd.byte[2])){
                newMatch->state = ST_NOMATCH;
    }
    else if(!(vector->srcIp.byte[3] >= rule->srcIpStart.byte[3]) ||
            !(vector->srcIp.byte[3] <= rule->srcIpEnd.byte[3])){
                newMatch->state = ST_NOMATCH;
    }

    else if(!(vector->dstIp.byte[0] >= rule->dstIpStart.byte[0]) ||
            !(vector->dstIp.byte[0] <= rule->dstIpEnd.byte[0])){
                newMatch->state = ST_NOMATCH;
    }
    else if(!(vector->dstIp.byte[1] >= rule->dstIpStart.byte[1]) ||
            !(vector->dstIp.byte[1] <= rule->dstIpEnd.byte[1])){
                newMatch->state = ST_NOMATCH;
    }
    else if(!(vector->dstIp.byte[2] >= rule->dstIpStart.byte[2]) ||
            !(vector->dstIp.byte[2] <= rule->dstIpEnd.byte[2])){
                newMatch->state = ST_NOMATCH;
    }
    else if(!(vector->dstIp.byte[3] >= rule->dstIpStart.byte[3]) ||
            !(vector->dstIp.byte[3] <= rule->dstIpEnd.byte[3])){
                newMatch->state = ST_NOMATCH;
    }

    else if(rule->srcPrtNeg &&
            (vector->srcPrt.value >= rule->srcPrtStart.value) &&
            (vector->srcPrt.value <= rule->srcPrtEnd.value)){
                newMatch->state = ST_NOMATCH;
    }
    else if(!rule->srcPrtNeg &&
            (!(vector->srcPrt.value >= rule->srcPrtStart.value) ||
            !(vector->srcPrt.value <= rule->srcPrtEnd.value))){
                newMatch->state = ST_NOMATCH;
    }

    else if(rule->dstPrtNeg &&
            (vector->dstPrt.value >= rule->dstPrtStart.value) &&
            (vector->dstPrt.value <= rule->dstPrtEnd.value)){
                newMatch->state = ST_NOMATCH;
    }
    else if(!rule->dstPrtNeg &&
            (!(vector->dstPrt.value >= rule->dstPrtStart.value) ||
            !(vector->dstPrt.value <= rule->dstPrtEnd.value))){
                newMatch->state = ST_NOMATCH;
    }

    else{
        newMatch->state = rule->action;
    }

    return SUCCESS;
}

error_t
print_match(struct match *match){
    switch(match->state){
        case(ST_DENY):
            printf("match: vector %d rule %d deny\n", match->vectorNr, match->ruleNr);
            break;
        case(ST_PERMIT):
            printf("match: vector %d rule %d permit\n", match->vectorNr, match->ruleNr);
            break;
        case(ST_REMARK):
            //ignore comment
            break;
        case(ST_NOMATCH):
            printf("nomatch: vector %d rule %d\n", match->vectorNr, match->ruleNr);
            break;
        default:
            printf("error: vector %d rule %d\n", match->vectorNr, match->ruleNr);
            break;
    }

    return SUCCESS;
}
