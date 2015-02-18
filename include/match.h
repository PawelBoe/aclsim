#ifndef MATCH_H
#define MATCH_H

#include "rule.h"
#include "vector.h"

typedef struct match match_t;

match_t *
check_match(vector_t*, rule_t*);

void
free_match(match_t*);

void
print_match(match_t*);

#endif
