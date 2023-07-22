#include "builtins.h"

const char *builtin_str[] = {
    "cd", "help", "exit"
};

const BUILTIN_STATUS (*builtin_func[]) (char **) = {
    &lsh_cd, &lsh_help, &lsh_exit
};

static int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

BUILTIN_STATUS lsh_launch_builtin(char **command)
{
    for (int i = 0; i < lsh_num_builtins(); i++) 
    {
        if (strcmp(command[0], builtin_str[i]) == 0) 
        {
            BUILTIN_STATUS status = (*builtin_func[i])(command);
            if (status != BUILTIN_SUCCESS)
            {
                perror("lsh: error executing command");
                return BUILTIN_FAILURE;
            }
            return status;
        }
    }

    return BUILTIN_NOT_FOUND;
}

/*
  Builtin function implementations.
*/

/**
   @brief Builtin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 0, to continue executing.
 */
static BUILTIN_STATUS lsh_cd(char **args)
{
    if (args[1] == NULL) 
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
        return BUILTIN_FAILURE;
    } 
    else 
    {
        if (chdir(args[1]) != 0) 
        {
            perror("lsh");
            return BUILTIN_FAILURE;
        }
    }
    return BUILTIN_SUCCESS;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
static BUILTIN_STATUS lsh_help(char **args)
{
    printf("Stephen Brennan's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < lsh_num_builtins(); i++) 
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return BUILTIN_SUCCESS;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
static BUILTIN_STATUS lsh_exit(char **args)
{
    exit(BUILTIN_SUCCESS);
    return BUILTIN_SUCCESS;
}