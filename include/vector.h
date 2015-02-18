#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector vector_t;

vector_t *
create_vector();

void
free_vector(vector_t*);

vector_t *
parse_vector(char*);

#endif
