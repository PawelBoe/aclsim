#include <stdio.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


struct match
check_match(struct vector *vector, struct rule *rule){
	int i;
	struct match newMatch;
	newMatch.vectorNr = vector->number;
	newMatch.ruleNr = rule->number;
	//missing stuff:
	//compare address range and port range
	//set appropriate state
	if (vector->protocol != rule->protocol){
		newMatch.state = -1;
		return newMatch;
	}
	for(i = 0; i < 4; i++){
		
	}
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
