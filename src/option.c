#include "option.h"
#include <string.h>

error_t
parse_option(optionAlt_t *newOption, int count, char *const arguments[])
{
    error_t status = SUCCESS;
    newOption->all = 0; //initialize to zero

    int i;
    for (i = 1; i < count; i++) {
        if (!strncmp(arguments[i], "-h\0", 3)) {
            newOption->help = 1;
        } else if (!strncmp(arguments[i], "-a\0", 3)) {
            newOption->allmatch = 1;
        } else if (!strncmp(arguments[i], "-n\0", 3)) {
            newOption->nomatch = 1;
        } else if (!strncmp(arguments[i], "-f\0", 3)) {
            newOption->filter = 1;
        } else {
            newOption->aclName = arguments[i];
        }
    }

    return status;
}
