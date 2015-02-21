#ifndef RULE_H
#define RULE_H

#include "ip.h"
#define RULESIZE 128


struct rule{
	int number;
	char status;
	char protocol;
	union ipAdr srcIp;
	char srcWild;
	union ipAdr dstIp;
	char dstWild;
	char operators[3];
	char operants[3];
	char log;
};

struct rule
parse_rule(char*, int);

#endif
