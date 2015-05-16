//Copyright (C) Pawel Böning, 2015
#ifndef MATCH_H
#define MATCH_H

#include "rule.h"
#include "vector.h"
#include "constants.h"


struct match {
    const struct rule *rulePtr;
    const struct vector *vectorPtr;
    state_t state;
};

extern error_t
check_match(struct match *newMatch, const struct vector *vector, const struct rule *rule);

extern error_t
print_match(const struct match *match, option_t option, int *matchCountm);

#endif
