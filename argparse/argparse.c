#include "argparse.h"
#include <stdlib.h>
#include <stdio.h>
#include <circular_ll.h>
#include <unistd.h>

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

int parser_add_option(parser_t * parser, char opt)
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

int parse_args(parser_t * parser, int argc, char ** argv)
{
    ssize_t size = circular_get_size(parser->options_list);
    size *= 2;
    char * options = calloc(sizeof(char), size + 1);

    for (ssize_t i = 0; i < size; i+=2)
    {
        option_t * tmp = circular_get_data(parser->options_list, (i / 2) + 1);
        options[i] = tmp->opt;
        options[i + 1] = ':';
    }

    char c = getopt(argc, argv, options);
    while (c != -1)
    {
        if (c == '?')
        {
            option_t search_option = {.opt = optopt};
            if (circular_search(parser->options_list, &search_option) == NULL)
            {
                printf("Unknown option: %c\n", optopt);
                free(options);
                return INVALID_OPT;
            }
            else
            {
                free(options);
                return ARGUMENT_REQUIRED;
            }
        }
        else
        {
            if (optarg[0] == '-')
            {
                printf("./main: option requires an argument -- '%c'\n", c);
                free(options);
                return ARGUMENT_REQUIRED;
            }
            else
            {
                option_t search_option = {.opt = c};
                option_t * tmp_option = circular_search(parser->options_list, &search_option);
                tmp_option->arg = optarg;
            }
        }

        c = getopt(argc, argv, options);
    }
    
    free(options);
    return 0;
}

char * parser_get_arg(parser_t * parser, char opt)
{
    if (NULL == parser)
    {
        return NULL;
    }
    option_t search_option = {.opt = opt};
    option_t * option = circular_search(parser->options_list, &search_option);
    char * return_data = option ? option->arg : NULL;
    return return_data;
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
    free(option);
}
// END OF SOURCE
