#include <stdio.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


struct match
check_match(struct vector *vector, struct rule *rule){
	struct match match;
	match.vectorNr = vector->number;
	match.ruleNr = rule->number;
	//missing stuff:
	//compare address range and port range
	//set appropriate state
	return match;
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
