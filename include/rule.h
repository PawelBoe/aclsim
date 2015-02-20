#ifndef RULE_H
#define RULE_H

#define RULESIZE 128


struct rule{
	int number;
	char status;
	char protocol;
	char srcIp;
	char srcWild;
	char dsrIp;
	char dstWild;
	char operators[3];
	char operants[3];
	char log;
};

struct rule
parse_rule(char*, int);

#endif
