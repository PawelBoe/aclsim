#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "rule.h"
#include "vector.h"

#define RAWSIZE 256


int
main(int argc, char **argv){

	FILE *acl;
	int vectorNr, ruleNr;
	char vectorbuf[RAWSIZE], rulebuf[RAWSIZE];
	struct match match;
	struct rule rule;
	struct vector vector;

	if(argc != 2){
		fprintf(stderr, "Usage: %s <aclfile> < vector(s)\n", argv[0]);
		return 1;
	}

	acl = fopen(argv[1], "r");

	if(acl == NULL){
		fprintf(stderr, "Unable to open file: %s\n", argv[1]);
		return 1;
	}

	for(vectorNr = 1; fgets(vectorbuf, RAWSIZE, stdin); vectorNr++){
		vector = parse_vector(vectorbuf, vectorNr);	//to do
		for(ruleNr = 1; fgets(rulebuf, RAWSIZE, acl) && match.state != NULL; ruleNr++){
			rule = parse_rule(rulebuf, ruleNr);	//to do
			match = check_match(&vector, &rule);	//to do
			print_match(&match);	//to do
		}
		rewind(acl);
	}

	fclose(acl);
	return 0;
}
