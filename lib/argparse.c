#include "argparse.h"
#include <stdlib.h>

typedef struct {
    datatype type;
    const char * opt;
}option_t;

struct parser_ {
    int arg_sz;
    char ** arguments;
    int opt_sz;
    option_t ** options;
};

parser_t * parser_init(void)
{
    parser_t * new = malloc(sizeof(parser_t));
    new->arg_sz = 0;
    new->arguments = NULL;
    new->opt_sz = 0;
    new->options = NULL;
    return new;
}

void parser_destroy(parser_t * parser)
{
    for (int i = 0; i < parser->opt_sz; i++)
    {
        free(parser->options[i]);
    }
    
    free(parser->options);
    free(parser);
}

int parser_add_option(parser_t * parser, const char * opt, datatype type)
{
    // TODO: Error handling
    option_t * option = malloc(sizeof(option_t));
    option->type = type;
    option->opt = opt;
    
    switch (parser->opt_sz)
    {
        case 0: ;
            parser->options = malloc(sizeof(option_t *));
            break;
        default: ;
            parser->options = realloc(parser->options, sizeof(option_t *) * (parser->opt_sz + 1));
    }
    
    parser->options[parser->opt_sz] = option;
    parser->opt_sz++;
    
    return 0;
}
