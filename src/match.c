//Copyright (C) Pawel Böning, 2015
#include <stdio.h>
#include "match.h"


static error_t
compare_protocol_match(int vectorProto, int ruleProto)
{
    error_t status = ERR_GENERIC;

    if (vectorProto == ruleProto) {
        status = SUCCESS;
    }
    else if (ruleProto == PROTO_IP) {
        status = SUCCESS;
    }

    return status;
}

static error_t
compare_address_match(union ipAdr vectorAdr, union ipAdr ruleAdrStart,
                      union ipAdr ruleAdrEnd)
{
    error_t status = SUCCESS;

    int i;
    for (i = 0; i < 4; i++) {
        if (!(vectorAdr.byte[i] >= ruleAdrStart.byte[i]) ||
           !(vectorAdr.byte[i] <= ruleAdrEnd.byte[i])){
            status |= ERR_GENERIC;
        }
    }

    return status;
}

static error_t
compare_port_match(union ipPrt vectorPrt, union ipPrt rulePrtStart,
                   union ipPrt rulePrtEnd, int rulePrtNeg)
{
    error_t status = SUCCESS;

    if (rulePrtNeg &&
            (vectorPrt.value >= rulePrtStart.value) &&
            (vectorPrt.value <= rulePrtEnd.value)) {
                status |= ERR_GENERIC;
    }
    else if (!rulePrtNeg &&
            (!(vectorPrt.value >= rulePrtStart.value) ||
            !(vectorPrt.value <= rulePrtEnd.value))) {
                status |= ERR_GENERIC;
    }

    return status;
}

error_t
check_match(struct match *newMatch, struct vector *vector, struct rule *rule)
{
    error_t status = SUCCESS;

    newMatch->vectorPtr = vector;
    newMatch->rulePtr = rule;

    if (rule->action == AC_REMARK) {
        newMatch->state = ST_REMARK;
    }
    else if (compare_protocol_match(vector->protocol, rule->protocol)
            != SUCCESS) {
        newMatch->state = ST_NOMATCH;
    }
    else if (compare_address_match(vector->srcAdr, rule->srcAdrStart,
                rule->srcAdrEnd) != SUCCESS) {
        newMatch->state = ST_NOMATCH;
    }
    else if (compare_address_match(vector->dstAdr, rule->dstAdrStart,
                rule->dstAdrEnd) != SUCCESS) {
        newMatch->state = ST_NOMATCH;
    }
    else if (compare_port_match(vector->srcPrt, rule->srcPrtStart,
                rule->srcPrtEnd, rule->srcPrtNeg) != SUCCESS) {
        newMatch->state = ST_NOMATCH;
    }
    else if (compare_port_match(vector->dstPrt, rule->dstPrtStart,
                rule->dstPrtEnd, rule->dstPrtNeg) != SUCCESS) {
        newMatch->state = ST_NOMATCH;
    }
    else {
        newMatch->state = (state_t)rule->action;
    }

    return status;
}

error_t
print_match(struct match *match, option_t option, int *matchCount)
{
    error_t status = SUCCESS;

    switch (match->state) {
    case ST_DENY:
        if (option == OP_STANDARD && *matchCount == 0) {
            printf("match(%d): vector<%d> rule<%d> deny\n",
                    *matchCount, match->vectorPtr->number,
                    match->rulePtr->number);
        }
        else if (option == OP_ALL || option == OP_VERBOSE) {
            printf("match(%d): vector<%d> rule<%d> deny\n",
                    *matchCount, match->vectorPtr->number,
                    match->rulePtr->number);
        }
        (*matchCount)++;
        break;
    case ST_PERMIT:
        if (option == OP_STANDARD && *matchCount == 0) {
            printf("match(%d): vector<%d> rule<%d> permit\n",
                    *matchCount, match->vectorPtr->number,
                    match->rulePtr->number);
        }
        else if (option == OP_ALL || option == OP_VERBOSE) {
            printf("match(%d): vector<%d> rule<%d> permit\n",
                    *matchCount, match->vectorPtr->number,
                    match->rulePtr->number);
        }
        else if (option == OP_FILTER && *matchCount == 0) {
            char strVector[VECTORSIZE];
            string_vector(strVector, match->vectorPtr);
            printf("%s\n", strVector);
        }
        (*matchCount)++;
        break;
    case ST_REMARK:
        //ignore comment
        break;
    case ST_NOMATCH:
        if (option == OP_NOMATCH || option == OP_VERBOSE) {
            printf("nomatch: vector<%d> rule<%d>\n",
                    match->vectorPtr->number,
                    match->rulePtr->number);
        }
        break;
    default:
        //shouldn´t reach this point
        fprintf(stderr, "error: vector<%d> rule<%d>\n",
                match->vectorPtr->number,
                match->rulePtr->number);
        status = ERR_GENERIC;
        break;
    }

    return status;
}
