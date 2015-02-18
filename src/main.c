#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "rule.h"
#include "vector.h"

#define RAWSIZE 100


int
main(int argc, char **argv){
	if(argc != 3){
		fprintf(stderr, "Usage: %s <aclfile> <vectorfile>\n", argv[0]);
		return 1;
	}

	//Check weather files exist
	FILE *acl;
	FILE *testfile;
	acl = fopen(argv[1], "r");
	testfile = fopen(argv[2], "r");

	if(acl == NULL){
		fprintf(stderr, "Unable to open file: %s\n", argv[1]);
		return 1;
	}
	if(testfile == NULL){
		fprintf(stderr, "Unable to open file: %s\n", argv[2]);
		return 1;
	}

	//check and match loop
	char rawVector[RAWSIZE];
	char rawRule[RAWSIZE];
	match_t *match;
	rule_t *rule;
	vector_t *vector;

	while(fgets(rawVector, RAWSIZE, testfile)){
		vector = parse_vector(rawVector);
		while(fgets(rawRule, RAWSIZE, acl) && !match){
			rule = parse_rule(rawRule);
			match = check_match(vector, rule);
			print_match(match);
			free_match(match);
			free_rule(rule);
		}
		free_vector(vector);
	}

	fclose(acl);
	fclose(testfile);
	return 0;
}
