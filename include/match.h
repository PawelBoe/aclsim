#ifndef MATCH_H
#define MATCH_H

#include "rule.h"
#include "vector.h"


struct match{
	int ruleNr;
	int vektorNr;
	char state[8];
};

struct match
check_match(struct vector*, struct rule*);

void
print_match(struct match*);

#endif
