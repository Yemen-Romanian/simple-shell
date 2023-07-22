#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include <sys/types.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define LSH_PIPE_DELIM "|"

char *lsh_read_line(void);
static char **lsh_split_line(char *line, const char *delimiter);
char **lsh_parse_commands(char *line);
char **lsh_parse_one_command(char *command);