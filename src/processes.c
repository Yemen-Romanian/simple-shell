#include "processes.h"
#include "builtins.h"


/**
  @brief Launch a program in a current process.
  @param args Null terminated list of arguments (including program name).
  @return 0 in case of success
 */
int lsh_launch_program(char *program)
{
    char **parsed_command = lsh_parse_one_command(program);
    BUILTIN_STATUS status = lsh_launch_builtin(parsed_command);
    if (status != BUILTIN_NOT_FOUND) exit(EXIT_SUCCESS);

    int execution_status = execvp(parsed_command[0], parsed_command);
    free(parsed_command);

    if (execution_status == -1) 
    {
        perror("lsh: error executing command");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/**
  @brief Launch a program in a new process (if it's not a builtin).
  @param args Null terminated list of arguments (including program name).
  @return 0 in case of success
 */

int lsh_launch_single_command(char *command)
{
    char **parsed_command = lsh_parse_one_command(command);
    BUILTIN_STATUS status = lsh_launch_builtin(parsed_command);
    if (status != BUILTIN_NOT_FOUND) return status;

    int program_status, execution_status;
    pid_t pid = fork();

    if (pid < 0)
    {
        free(parsed_command);
        perror("lsh: error forking process");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        execution_status = execvp(parsed_command[0], parsed_command);
        free(parsed_command);
        if (execution_status == -1) 
        {
            perror("lsh: error executing command");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else 
    {
        do 
        {
            waitpid(pid, &program_status, WUNTRACED);
        } 
        while (!WIFEXITED(program_status) && !WIFSIGNALED(program_status));
    }

    return EXIT_SUCCESS;
}


/**
   @brief Execute commands separated by pipeline
   @param args Null terminated list of arguments.
   @return 0 if the shell should continue running, 1 if it should terminate
 */
int lsh_execute_pipeline(char **args, int commands_number)
{
    int command_counter = 0;
    int current_fds[2];
    int prev_fds[2];
    int process_status;
    pid_t pid;

    if (!commands_number || !strlen(args[0]))
    {
        return EXIT_SUCCESS;
    }

    for (int command_counter = 0; command_counter < commands_number; command_counter++)
    {
        if (command_counter < commands_number - 1)
            if (pipe(current_fds) == -1)
            {
                perror("lsh: error creating pipe");
                exit(EXIT_FAILURE);
            }

        pid = fork();

        if (pid < 0)
        {
            perror("lsh: error while forking");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (command_counter > 0)
            {
                if (dup2(prev_fds[READ_PIPE], STDIN_FILENO) == -1)
                {
                    perror("lsh: error while duping on READ_PIPE");
                    exit(EXIT_FAILURE);
                }
                close(prev_fds[READ_PIPE]);
                close(prev_fds[WRITE_PIPE]);
            }

            if (command_counter < commands_number - 1)
            {
                close(current_fds[READ_PIPE]);
                if (dup2(current_fds[WRITE_PIPE], STDOUT_FILENO) == - 1)
                {
                    perror("lsh: error while duping on WRITE_PIPE");
                    exit(EXIT_FAILURE);
                }
                close(current_fds[WRITE_PIPE]);
            }

            lsh_launch_program(args[command_counter]);
        }
        else
        {
            if (command_counter > 0)
            {
                close(prev_fds[READ_PIPE]);
                close(prev_fds[WRITE_PIPE]);
            }

            if (command_counter < commands_number - 1)
            {
                prev_fds[READ_PIPE] = current_fds[READ_PIPE];
                prev_fds[WRITE_PIPE] = current_fds[WRITE_PIPE];
            }

            do
            {
                waitpid(pid, &process_status, WUNTRACED);
            } 
            while (!WIFEXITED(process_status) && !WIFSIGNALED(process_status));
        }
    }

    close(prev_fds[READ_PIPE]);
    close(prev_fds[WRITE_PIPE]);

    return EXIT_SUCCESS;
}

int lsh_execute(char **command)
{
    int commands_number = 0;
    for (int i = 0; command[i]; i++, commands_number++);

    if (!commands_number || !strlen(command[0]))
    {
        return EXIT_SUCCESS;
    }

    if (commands_number == 1) return lsh_launch_single_command(command[0]);
    
    return lsh_execute_pipeline(command, commands_number);
}
