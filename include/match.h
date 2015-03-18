#ifndef MATCH_H
#define MATCH_H

#include "rule.h"
#include "vector.h"
#include "constants.h"


struct match{
    int ruleNr;
    int vectorNr;
    int state;
};

extern error_t
check_match(struct match *newMatch, struct vector *vector, struct rule *rule);

extern error_t
print_match(struct match *match);

#endif
