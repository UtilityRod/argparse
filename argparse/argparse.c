#include "argparse.h"
#include <stdlib.h>
#include <stdio.h>
#include <circular_ll.h>

typedef struct {
    char opt;
    char * arg;
}option_t;

struct parser {
    circular_list_t * options_list;
};

static int options_compare(const void * arg1, const void * arg2);
static void options_destroy(void * arg);

parser_t * parser_create(void)
{
    parser_t * parser = calloc(sizeof(*parser), 1);
    
    if (parser != NULL)
    {
        parser->options_list = circular_create(options_compare, options_destroy);
    }

    return parser;
}

void parser_destroy(parser_t * parser)
{
    if (parser != NULL)
    {
        if (parser->options_list != NULL)
        {
            circular_destroy(parser->options_list);
        }

        free(parser);
        parser = NULL;
    }

    return;
}

ssize_t parser_add_option(parser_t * parser, char opt)
{
    if (NULL == parser)
    {
        return PARSER_NULL;
    }
    else if (NULL == parser->options_list)
    {
        return LIST_NULL;
    }
    else if (((opt >= 'A') && (opt <= 'Z')) || ((opt >= 'a') && (opt <= 'z')))
    {
        option_t * option = calloc(sizeof(*option), 1);

        if (option != NULL)
        {
            option->opt = opt;
            circular_insert(parser->options_list, option, FRONT);
        }
    }
    else
    {
        return INVALID_OPT;
    }

    return circular_get_size(parser->options_list);
}

static int options_compare(const void * arg1, const void * arg2)
{
    option_t * option1 = (option_t *)arg1;
    option_t * option2 = (option_t *)arg2;
    return option2->opt - option1->opt;
}

static void options_destroy(void * arg)
{
    option_t * option = (option_t *)arg;
    if (option->arg != NULL)
    {
        free(option->arg);
    }
    free(option);
}
// END OF SOURCE
