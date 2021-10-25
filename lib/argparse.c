#include "argparse.h"
#include <stdlib.h>

typedef struct {
    datatype type;
    char * value;
}option_t;

struct parser_ {
    char ** arguments;
    option_t ** options;
};

parser_t * parser_init(void)
{
    parser_t * new = malloc(sizeof(parser_t));
    return new;
}

void parser_destroy(parser_t * parser)
{
    free(parser);
}
