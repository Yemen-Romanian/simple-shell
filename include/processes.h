#ifndef PROCESSES
#define PROCESSES

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "builtins.h"

int lsh_launch(char **args);
int lsh_execute(char **args);

#endif