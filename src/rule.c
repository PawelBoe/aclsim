#include "rule.h"


int
valid_rule(char *rawRule){
	return 0;
}

//hint: count how many tokens there are
// then determine which token lies where

struct rule
parse_rule(char *rawRule, int lineNr){
	int i,j;
	struct rule newRule;
	int tokenCount = 0;
	char token[15][RULESIZE];
	//missing stuff
	for(i = 0; i < 15 ; i++){
		for(j = 0; j < RULESIZE-1; i++){
			token[i][j] = *rawRule;
			rawRule++;
		}
		rawRule++;
		tokenCount++;
	}
    newRule.number = token[1][1];

	switch(tokenCount){
	case 5: break;
	case 6: break;
	case 7: break;
	case 8: break;
	case 9: break;
	case 10: break;
	case 11: break;
	case 12: break;
	}

	return newRule;
}

