#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "rule.h"
#include "vector.h"

#define RAWSIZE 100


int
main(int argc, char **argv){
	if(argc != 3){
		fprintf(stderr, "Usage: %s <aclfile> < vector(s)\n", argv[0]);
		return 1;
	}

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

	int vectorNr, ruleNr;
	char rawVector[RAWSIZE], rawRule[RAWSIZE];
	struct match match;
	struct rule rule;
	struct vector vector;

	for(vectorNr = 1; fgets(rawVector, RAWSIZE, testfile); vectorNr++){
		vector = parse_vector(rawVector, vectorNr);	//to do
		for(ruleNr = 1; fgets(rawRule, RAWSIZE, acl) && match.state != NULL; ruleNr++){
			rule = parse_rule(rawRule, ruleNr);	//to do
			match = check_match(vector, rule);	//to do
			print_match(match);	//to do
		}
		rewind(acl);
	}

	fclose(acl);
	fclose(testfile);
	return 0;
}
