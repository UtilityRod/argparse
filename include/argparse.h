#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdbool.h>

typedef struct parser_ parser_t;
typedef enum {INT, STR} datatype;

parser_t * parser_init(void);
void parser_destroy(parser_t * parser);
int parser_add_option(parser_t * parser, const char opt, datatype type, unsigned int nargs);
int parser_parse_args(parser_t * parser, int argc, char ** argv);
bool option_check_invoked(parser_t * parser, char opt);
char * option_get_argument(parser_t * parser, char opt);

#endif
