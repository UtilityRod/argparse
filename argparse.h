#ifndef _ARGPARSE_H_
#define _ARGPARSE_H_

#include <sys/types.h>

typedef struct parser parser_t;

typedef enum { PARSER_NULL = -1, LIST_NULL = -2, INVALID_OPT = -3, ARGUMENT_REQUIRED = -4} error_t;

parser_t * parser_create(void);
void parser_destroy(parser_t * parser);
int parser_add_option(parser_t * parser, char opt);
int parse_args(parser_t * parser, int argc, char ** argv);
char * parser_get_arg(parser_t * parser, char opt);

#endif
