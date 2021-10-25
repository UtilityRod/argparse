#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdbool.h>

typedef struct parser_ parser_t;
typedef enum {INT, STR} datatype;

parser_t * parser_init(void);
void parser_destroy(parser_t * parser);
int parser_add_option(parser_t * parser, const char opt, datatype type, unsigned int nargs);
int parser_parse_args(parser_t * parser, int argc, char ** argv);
bool parser_opt_invoked(parser_t * parser, char opt);
char * parser_get_optarg(parser_t * parser, char opt);
char ** parser_get_arguments(parser_t * parser);

#endif
