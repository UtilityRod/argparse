#ifndef _ARGPARSE_H_
#define _ARGPARSE_H_

typedef struct parser parser_t;
typedef enum {INT, STR} datatype;

parser_t * parser_create(void);
void parser_destroy(parser_t * parser);

#endif
