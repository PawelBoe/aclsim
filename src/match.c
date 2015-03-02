#include <stdio.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


struct match
check_match(struct vector *vector, struct rule *rule){
	struct match newMatch;
	newMatch.vectorNr = vector->number;
	newMatch.ruleNr = rule->number;

	if (vector->protocol != rule->protocol){
		newMatch.state = -1;
		return newMatch;
	}

	if(!(vector->srcIp.byte[0] >= rule->srcIp_start.byte[0]) ||
	   !(vector->srcIp.byte[0] <= rule->srcIp_end.byte[0])){
		newMatch.state = -1;
		return newMatch;
	}
	if(!(vector->srcIp.byte[1] >= rule->srcIp_start.byte[1]) ||
	   !(vector->srcIp.byte[1] <= rule->srcIp_end.byte[1])){
		newMatch.state = -1;
		return newMatch;
	}
	if(!(vector->srcIp.byte[2] >= rule->srcIp_start.byte[2]) ||
	   !(vector->srcIp.byte[2] <= rule->srcIp_end.byte[2])){
		newMatch.state = -1;
		return newMatch;
	}
	if(!(vector->srcIp.byte[3] >= rule->srcIp_start.byte[3]) ||
	   !(vector->srcIp.byte[3] <= rule->srcIp_end.byte[3])){
		newMatch.state = -1;
		return newMatch;
	}

	newMatch.state = rule->action;
	return newMatch;
}

void
print_match(struct match *match){
	switch(match->state){
		case(0):
			printf("match: vectorNr.%d ruleNr.%d deny", match->vectorNr, match->ruleNr);
			break;
		case(1):
			printf("match: vectorNr.%d ruleNr.%d permit", match->vectorNr, match->ruleNr);
			break;
		case(-1):
			printf("nomatch: vectorNr.%d ruleNr.%d", match->vectorNr, match->ruleNr);
			break;
		default:
			printf("error: vectorNr.%d ruleNr.%d", match->vectorNr, match->ruleNr);
			break;
	}
}
