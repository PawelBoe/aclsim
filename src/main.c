//Copyright (C) Pawel Böning, 2015
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "match.h"
#include "rule.h"
#include "vector.h"


void
print_usage(char *progName);

void
print_help(char *progName);

void
process_acl(FILE *acl, int nomatchFlag, int allFlag);

void
skip_line(FILE *stream);

int
main(int argc, char **argv){

    FILE *acl;
    int option = 0;
    char *aclName = argv[1];
    int nomatchFlag = 0;
    int allFlag = 0;

    if(argc != 2 && argc != 3){
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    while((option = getopt(argc, argv, "hs:a:n:v:")) != -1){
        switch (option) {
            case 'h': //help
                print_help(argv[0]);
                break;
            case 's': //standard
                nomatchFlag = 0;
                allFlag = 0;
                aclName = optarg;
                break;
            case 'a': //show all matches
                nomatchFlag = 0;
                allFlag = 1;
                aclName = optarg;
                break;
            case 'n': //show not matching
                nomatchFlag = 1;
                allFlag = 0;
                aclName = optarg;
                break;
            case 'v': //show verbose (nomatch + all)
                nomatchFlag = 1;
                allFlag = 1;
                aclName = optarg;
                break;
            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    acl = fopen(aclName, "r");
    if(acl == NULL){
        fprintf(stderr, "Unable to open file: %s\n", aclName);
        return EXIT_FAILURE;
    }

    process_acl(acl, nomatchFlag, allFlag);
    fclose(acl);

    return EXIT_SUCCESS;
}

void
process_acl(FILE *acl, int nomatchFlag, int allFlag){
    int vectorNr, ruleNr;
    char vectorbuf[VECTORSIZE], rulebuf[RULESIZE];
    struct match match;
    struct rule rule;
    struct vector vector;

    for(vectorNr = 0; fgets(vectorbuf, VECTORSIZE-1, stdin); ){
        if(vectorbuf[strlen(vectorbuf)-1] != '\n'){
            skip_line(stdin);
        }
        vectorbuf[strlen(vectorbuf)-1] = '\0';
        if(parse_vector(&vector, vectorbuf, &vectorNr) != SUCCESS){
            fprintf(stderr, "Error occured in vector %d\n", vector.number);
            continue;
        }
        for(ruleNr = 0; fgets(rulebuf, RULESIZE-1, acl); ){
            if(rulebuf[strlen(rulebuf)-1] != '\n'){
                skip_line(acl);
            }
            rulebuf[strlen(rulebuf)-1] = '\0';
            if(parse_rule(&rule, rulebuf, &ruleNr) != SUCCESS){
                fprintf(stderr, "Error occured in rule %d\n", rule.number);
                continue;
            }
            check_match(&match, &vector, &rule);
            print_match(&match, nomatchFlag);
        }
        rewind(acl);
    }
}

void
print_usage(char *progName){
        fprintf(stderr,
        "Usage: %s\t [-h]\n"
               "\t\t [-s] [aclFile]\n"
               "\t\t [-a|-n|-v] [aclFile]\n",
               progName);
}

void print_help(char *progName){
   print_usage(progName);

}

void
skip_line(FILE *stream){
    while(getc(stream) != '\n');
}
