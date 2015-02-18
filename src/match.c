#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "rule.h"
#include "vector.h"

struct match{
	int ruleNr;
	int vektorNr;
	char state[8];
};

match_t *
check_match(vector_t *vector, rule_t *rule){
	//missing stuff
	match_t *retTest = malloc(sizeof(match_t));
	return retTest;
}

void
free_match(match_t *oldMatch){
	free(oldMatch);
}

void
print_match(match_t* match){
	puts("TEST"); //Test
}
