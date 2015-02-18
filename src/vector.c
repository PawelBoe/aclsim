#include <stdlib.h>
#include "vector.h"

struct vector{
	int number;
	char *protocol;
	char *srcIp;
	char *srcPrt;
	char *dstIp;
	char *dstPrt;
	char *flags;
	char *comment;
};

vector_t *
create_vector(){
	vector_t *newVector; 
	newVector = malloc(sizeof(vector_t));
	return newVector;
}

void
free_vector(vector_t *oldVector){
	free(oldVector);
}

vector_t *
parse_vector(char *rawRule){
	vector_t *newVector = create_vector();
	//missing stuff
	return newVector;
}
