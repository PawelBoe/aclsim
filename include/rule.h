#ifndef RULE_H
#define RULE_H

typedef struct rule rule_t;

rule_t *
create_rule();

void
free_rule(rule_t*);

rule_t *
parse_rule(char*);

#endif
