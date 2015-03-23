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
process_acl(FILE *acl, option_t option);

void
skip_line(FILE *stream);

int
main(int argc, char **argv){

    FILE *acl;
    int opt = 0;
    char *aclName = argv[1];
    option_t option = OP_STANDARD;

    if(argc != 2 && argc != 3){
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    while((opt = getopt(argc, argv, "hs:a:n:v:f:")) != -1){
        switch (opt) {
            case 'h': //help
                option = OP_HELP;
                print_help(argv[0]);
                exit(EXIT_SUCCESS);
                break;
            case 's': //standard
                option = OP_STANDARD;
                aclName = optarg;
                break;
            case 'a': //show all matches
                option = OP_ALL;
                aclName = optarg;
                break;
            case 'n': //show not matching
                option = OP_NOMATCH;
                aclName = optarg;
                break;
            case 'v': //show verbose (nomatch + all)
                option = OP_VERBOSE;
                aclName = optarg;
                break;
            case 'f': //filter vectors
                option = OP_FILTER;
                aclName = optarg;
                break;
            default:
                option = OP_UNKNOWN;
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    acl = fopen(aclName, "r");
    if(acl == NULL){
        fprintf(stderr, "Unable to open file: %s\n", aclName);
        return EXIT_FAILURE;
    }

    process_acl(acl, option);
    fclose(acl);

    return EXIT_SUCCESS;
}

void
process_acl(FILE *acl, option_t option){
    int vectorNr, ruleNr, matchCount;
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
            fprintf(stderr, COLOR_RED
                    ">> Error occured in vector %d\n"
                    ">> Terminating program ..\n",
                    vector.number);
            return;
        }

        for(ruleNr = 0, matchCount = 0; fgets(rulebuf, RULESIZE-1, acl); ){
            if(rulebuf[strlen(rulebuf)-1] != '\n'){
                skip_line(acl);
            }
            rulebuf[strlen(rulebuf)-1] = '\0';

            if(parse_rule(&rule, rulebuf, &ruleNr) != SUCCESS){
                fprintf(stderr, COLOR_RED
                        ">>Error occured in rule %d\n"
                        ">>Terminating program ..\n",
                        rule.number);
                return;
            }

            check_match(&match, &vector, &rule);
            print_match(&match, option, &matchCount);
        }

        rewind(acl);
    }
}

void
print_usage(char *progName){
        printf(
        "Usage: %s\t [-h]\n"
               "\t\t [-s] [aclFile]\n"
               "\t\t [-a|-n|-v] [aclFile]\n"
               "\t\t [-f] [aclFile]\n",
               progName);
}

void print_help(char *progName){
   print_usage(progName);
   printf("Simulate CISCO ACL functionality by applying rules to a "
           "fixed test\nvector file. Vectors are read from standard "
           "input and can therefore\nbe piped into the program: "
           "%s [option] [aclFile] < (vectorFile)\n\n"
           "Possible options are:\n"
           "-h \t\tshow help\n"
           "-s (standard)\tshow first match ONLY\n"
           "-a \t\tshow all matches, not only the first ones\n"
           "-n \t\tshow not matching rules and corresponding vectors ONLY\n"
           "-v \t\tshow verbose output (like using both -a and -n)\n"
           "-f \t\tfilter and print permitted vectors to stdout\n"
           , progName);
}

void
skip_line(FILE *stream){
    while(getc(stream) != '\n');
}
