#include <stdio.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


void
check_match(struct match *newMatch, struct vector *vector, struct rule *rule){
    newMatch->vectorNr = vector->number;
    newMatch->ruleNr = rule->number;

    if (rule->action == AC_REMARK){
        newMatch->state = ST_NOMATCH;
    }
    else if (vector->protocol != rule->protocol){
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
    else{
        newMatch->state = rule->action;
    }
}

void
print_match(struct match *match){
    switch(match->state){
        case(ST_DENY):
            printf("match: vectorNr.%d ruleNr.%d deny\n", match->vectorNr, match->ruleNr);
            break;
        case(ST_PERMIT):
            printf("match: vectorNr.%d ruleNr.%d permit\n", match->vectorNr, match->ruleNr);
            break;
        case(ST_NOMATCH):
            printf("nomatch: vectorNr.%d ruleNr.%d\n", match->vectorNr, match->ruleNr);
            break;
        default:
            printf("error: vectorNr.%d ruleNr.%d\n", match->vectorNr, match->ruleNr);
            break;
    }
}
