#include "argparse.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    bool invoked;
    datatype type;
    char * opt;
    unsigned int nargs;
    char * optarg;
}option_t;

struct parser_ {
    int arg_sz;
    char ** arguments;
    unsigned int str_sz;
    option_t ** options;
    unsigned int opt_amt;
};

enum {OPT_SIZE = 53};

static char * arg_string_get(parser_t * parser);
static int option_set_invoked(parser_t * parser, char opt, char * optarg);
static int get_index(char letter);

parser_t * parser_init(void)
{
    parser_t * new = malloc(sizeof(parser_t));
    new->options = calloc(sizeof(option_t), OPT_SIZE);
    new->arg_sz = 0;
    new->arguments = NULL;
    new->opt_amt = 0;
    new->str_sz = 2;
    return new;
}

void parser_destroy(parser_t * parser)
{
    for (int i = 0; i < OPT_SIZE; i++)
    {
        if (parser->options[i])
        {
            free(parser->options[i]->opt);
            free(parser->options[i]);
        }
    }
    
    free(parser->options);
    
    if (parser->arguments)
    {
        free(parser->arguments);
    }
    
    free(parser);
}

int parser_add_option(parser_t * parser, const char opt, datatype type, unsigned int nargs)
{
    // TODO: Error handling
    option_t * option = malloc(sizeof(option_t));
    option->optarg = NULL;
    option->type = type;
    option->nargs = nargs;
    option->opt = malloc(sizeof(char) * (nargs + 2));
    option->opt[nargs + 1] = '\0';
    option->invoked = false;
    
    switch (nargs)
    {
        case 1: ;
            sprintf(option->opt, "%c:", opt);
            break;
        default:
            sprintf(option->opt, "%c", opt);
    }
    
    int idx = get_index(opt);
    
    if (idx == -1)
    {
        return -1;
    }
    
    parser->options[idx] = option;
    parser->opt_amt += 1;
    parser->str_sz += (1 + nargs);
    
    return 0;
}

int parser_parse_args(parser_t * parser, int argc, char ** argv)
{
    int opt = 0;
    char * arg_string = arg_string_get(parser);
    int rtr_flag = 0;
    unsigned int opt_found = 0;
    while((opt = getopt(argc, argv, arg_string)) != -1)
    {
        if (isalpha(opt))
        {
            opt_found += option_set_invoked(parser, opt, optarg);
            continue;
        }
        
        if (opt == ':')
        {
            printf("option needs a value\n");
            rtr_flag = -1;
            break;
        }
        
        if (opt == '?')
        {
            printf("Unknown option: %c\n", optopt);
            rtr_flag = -1;
            break;
        }
    }
    
    free(arg_string);
    
    if((parser->arg_sz = argc - (opt_found + 1)) == 0)
    {
        return rtr_flag;
    }
    
    parser->arguments = malloc(sizeof(char *) * (parser->arg_sz + 1));
    unsigned int arg_idx = 0;
    
    for (; optind< argc; optind++)
    {
        parser->arguments[arg_idx++] = argv[optind];
    }
    
    parser->arguments[arg_idx] = NULL;
    return rtr_flag;
}

bool parser_opt_invoked(parser_t * parser, char opt)
{
    int idx = get_index(opt);
    
    if (parser->options[idx] == NULL)
    {
        return -1;
    }
    else
    {
        return parser->options[idx]->invoked;
    }
}

char * parser_get_optarg(parser_t * parser, char opt)
{
    int idx = get_index(opt);
    
    if (parser->options[idx] == NULL)
    {
        return NULL;
    }
    
    
    if (parser->options[idx]->invoked && parser->options[idx]->optarg)
    {
        return parser->options[idx]->optarg;
    }
    else 
    {
        return NULL;
    }
}

char ** parser_get_arguments(parser_t * parser)
{
    return parser->arguments;
}

static char * arg_string_get(parser_t * parser)
{
    char * arg_string = calloc(sizeof(char), parser->str_sz);
    arg_string[0] = ':';
    arg_string[parser->str_sz - 1] = '\0';
    int str_idx = 1;
    
    for (unsigned int i = 0; i < OPT_SIZE; i++)
    {
        if (parser->options[i])
        {
            strcpy(&arg_string[str_idx], parser->options[i]->opt);
            str_idx += (1 + parser->options[i]->nargs);
        }
    }

    return arg_string;
}

static int option_set_invoked(parser_t * parser, char opt, char * optarg)
{
    int index = get_index(opt);
    int arg_amount = 1;
    option_t * option = parser->options[index];
    option->invoked = true;
    if (optarg)
    {
        option->optarg = optarg;
        arg_amount++;
    }
    
    return arg_amount;
}

static int get_index(char letter)
{
    int index = 0;
    
    if (letter >= 0x41 && letter <= 0x5A)
    {
        index = (letter % 0x41) + 27;
    }
    else if (letter >= 0x61 && letter <= 0x7A)
    {
        index = (letter % 0x61);
    }
    else
    {
        index = -1;
    }

    return index;
}
// END OF SOURCE
