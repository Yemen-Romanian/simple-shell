#ifndef BUILTINS
#define BUILTINS

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    BUILTIN_SUCCESS,
    BUILTIN_FAILURE,
    BUILTIN_NOT_FOUND
} BUILTIN_STATUS;

/*
  Function Declarations for builtin shell commands:
 */
static BUILTIN_STATUS lsh_cd(char **args);
static BUILTIN_STATUS lsh_help(char **args);
static BUILTIN_STATUS lsh_exit(char **args);
static int lsh_num_builtins();
BUILTIN_STATUS lsh_launch_builtin(char **);

/*
  List of builtin commands, followed by their corresponding functions.
 */
extern const char *builtin_str[];
extern const BUILTIN_STATUS (*builtin_func[]) (char **);

#endif