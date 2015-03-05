#include <stdio.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


int
main(int argc, char **argv){

	FILE *acl;
	int vectorNr, ruleNr;
	char vectorbuf[VECTORSIZE], rulebuf[RULESIZE];
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

	for(vectorNr = 0; fgets(vectorbuf, VECTORSIZE-1, stdin); vectorNr++){
		if(!valid_vector(vectorbuf)){
			fprintf(stderr, "Vector Nr %d. is not valid\n", vectorNr);
			continue;
		}
		vector = parse_vector(vectorbuf, vectorNr);
		for(ruleNr = 0; fgets(rulebuf, RULESIZE-1, acl); ruleNr++){
			if(!valid_rule(rulebuf)){
				fprintf(stderr, "Rule Nr %d. is not valid\n", ruleNr);
				continue;
			}
			//missing match break, ignore remarks
			rule = parse_rule(rulebuf, ruleNr);	//to do
			match = check_match(&vector, &rule);
			print_match(&match);
		}
		rewind(acl);
	}
	fclose(acl);
	return 0;
}
