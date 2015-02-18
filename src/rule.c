#include <stdlib.h>
#include "rule.h"

struct rule{
	//missing stuff
};

rule_t *
create_rule(){
	rule_t *newRule;
	newRule = malloc(sizeof(rule_t));
	return newRule;
}

void
free_rule(rule_t *oldRule){
	free(oldRule);
}

rule_t *
parse_rule(char *rawRule){
	rule_t *newRule = create_rule();
	//missing stuff
	return newRule;
}
