#ifndef BUILTINS
#define BUILTINS

#include <stdio.h>
#include <unistd.h>

/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_num_builtins();

/*
  List of builtin commands, followed by their corresponding functions.
 */
extern const char *builtin_str[];
extern const int (*builtin_func[]) (char **);

#endif