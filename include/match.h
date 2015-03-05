#ifndef MATCH_H
#define MATCH_H

#include "rule.h"
#include "vector.h"
#include "constants.h"


struct match{
	int ruleNr;
	int vektorNr;
	int state; //deny 0, permit 1, nomatch -1
};

struct match
check_match(struct vector *vector, struct rule *rule);

void
print_match(struct match *match);

#endif
