//Copyright (C) Pawel Böning, 2015
#ifndef RULE_H
#define RULE_H

#include "ip.h"
#include "constants.h"


struct rule{
    int number;     //position of rule in ACL (starting with 0)
    int action;     //rule action (0-deny 1-permit, 2-remark)
    int protocol;   //value of used communication protocol

    union ipAdr srcAdrStart;    //source port range
    union ipAdr srcAdrEnd;

    union ipAdr dstAdrStart;    //destination port range
    union ipAdr dstAdrEnd;

    union ipPrt srcPrtStart;  //source port range
    union ipPrt srcPrtEnd;
    int srcPrtNeg;            //neq detection

    union ipPrt dstPrtStart;  //destination port range
    union ipPrt dstPrtEnd;
    int dstPrtNeg;            //neq detection
};

extern error_t
parse_rule(struct rule *newRule, char *rawRule, int *lineNr);

#endif
