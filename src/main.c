#include <stdio.h>
#include <string.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


void
skipLine(FILE *stream);

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

    //missing match break, ignore remarks, validity (errorcodes)
    for(vectorNr = 0; fgets(vectorbuf, VECTORSIZE-1, stdin); vectorNr++){
        if(vectorbuf[strlen(vectorbuf)-1] != '\n'){
            skipLine(stdin);
        }
        vectorbuf[strlen(vectorbuf)-1] = '\0';
        if(parse_vector(&vector, vectorbuf, vectorNr) != SUCCESS){ //errorcodes
            continue;
        }
        for(ruleNr = 0; fgets(rulebuf, RULESIZE-1, acl); ruleNr++){
            if(rulebuf[strlen(rulebuf)-1] != '\n'){
                skipLine(acl);
            }
            rulebuf[strlen(rulebuf)-1] = '\0';
            if(parse_rule(&rule, rulebuf, ruleNr) != SUCCESS){ //errorcodes
                continue;
            }
            check_match(&match, &vector, &rule); //errorcodes
            print_match(&match); //errorcodes
        }
        rewind(acl);
    }
    fclose(acl);
    return 0;
}

void
skipLine(FILE *stream){
    while(getc(stream) != '\n');
}
