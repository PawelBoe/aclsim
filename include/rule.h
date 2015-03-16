#ifndef RULE_H
#define RULE_H

#include "ip.h"
#include "constants.h"


struct rule{
    int number;     //position of rule in ACL (starting with 0)
    int action;     //rule action (0-deny 1-permit, 2-remark)
    int protocol;   //value of used communication protocol

    union ipAdr srcIpStart;    //source port range
    union ipAdr srcIpEnd;

    union ipAdr dstIpStart;    //destination port range
    union ipAdr dstIpEnd;

    union ipPort srcPrtStart;  //source port range
    union ipPort srcPrtEnd;

    union ipPort dstPrtStart;  //destination port range
    union ipPort dstPrtEnd;
};

extern error_t
parse_rule(struct rule *newRule, char *rawRule, int lineNr);

#endif
