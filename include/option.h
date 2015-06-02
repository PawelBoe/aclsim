//Copyright (C) Pawel Böning, 2015
#ifndef OPTION_H
#define OPTION_H

#include "constants.h"


typedef struct option {
    union {
        struct {
            unsigned char help:1;
            unsigned char allmatch:1;
            unsigned char nomatch:1;
            unsigned char filter:1;
            unsigned char reserved:4;
        };
        unsigned char all;
    };
    const char *aclName;
} optionAlt_t;

extern error_t
parse_option(optionAlt_t *newOption, int count, const char *arguments[]);

#endif
