#ifndef PROCESSES
#define PROCESSES

#define READ_PIPE 0
#define WRITE_PIPE 1

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "builtins.h"
#include "parser.h"

static int lsh_launch_program(char *);
static int lsh_launch_single_command(char *);
static int lsh_execute_pipeline(char **, int);
int lsh_execute(char **);

#endif