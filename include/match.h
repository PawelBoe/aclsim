//Copyright (C) Pawel Böning, 2015
#ifndef MATCH_H
#define MATCH_H

#include "rule.h"
#include "vector.h"
#include "constants.h"


struct match{
    struct rule *rulePtr;
    struct vector *vectorPtr;
    state_t state;
};

extern error_t
check_match(struct match *newMatch, struct vector *vector, struct rule *rule);

extern error_t
print_match(struct match *match, option_t option, int *matchCountm);

#endif
