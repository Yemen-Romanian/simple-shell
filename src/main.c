/***************************************************************************//**

  @file         main.c

  @author       Stephen Brennan

  @date         Thursday,  8 January 2015

  @brief        LSH (Libstephen SHell)

*******************************************************************************/

#include "processes.h"
#include "parser.h"
#include "builtins.h"


/**
   @brief Loop getting input and executing it.
 */
void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do 
    {
        printf("> ");
        line = lsh_read_line();
        args = lsh_parse_commands(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } 
    while (!status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
    // Load config files, if any.

    // Run command loop.
    lsh_loop();

    // Perform any shutdown/cleanup.

    return EXIT_SUCCESS;
}

