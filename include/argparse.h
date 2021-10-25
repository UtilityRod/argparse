#ifndef ARGPARSE_H
#define ARGPARSE_H

typedef struct parser_ parser_t;
typedef enum {INT, STR} datatype;

parser_t * parser_init(void);
void parser_destroy(parser_t * parser);
int parser_add_option(parser_t * parser, const char opt, datatype type, unsigned int nargs);
int parser_parse_args(parser_t * parser, int argc, char ** argv);

#endif
