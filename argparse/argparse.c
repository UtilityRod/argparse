#include "argparse.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool invoked;
    datatype type;
    char * opt;
    unsigned int nargs;
    char * arg;
}option_t;

struct parser {
    int arg_sz;
    char ** arguments;
    unsigned int str_sz;
    option_t ** options;
    unsigned int opt_amt;
};

parser_t * parser_create(void)
{
    parser_t * parser = calloc(sizeof(*parser), 1);
    return parser;
}

void parser_destroy(parser_t * parser)
{
    free(parser);
    return;
}
// END OF SOURCE
