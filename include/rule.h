#ifndef RULE_H
#define RULE_H

#include "ip.h"
#include "constants.h"


int
valid_rule(char *rawRule);

struct rule{
	int number; 	//position of rule in ACL (starting with 0)
	int action; 	//rule action (0-deny 1-permit)
	int protocol; 	//value of used communication protocol

	union ipAdr srcIp_start; 	//source port range
	union ipAdr srcIp_end;

	union ipAdr dstIp_start; 	//destination port range
	union ipAdr dstIp_end;

	union ipPort srcPrt_start; 	//source port range
	union ipPort srcPrt_end;

	union ipPort dstPrt_start; 	//destination port range
	union ipPort dstPrt_end;
};

struct rule
parse_rule(char *rawRule, int lineNr);

#endif
