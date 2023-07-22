#include "parser.h"

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{
	char *line = NULL;
	ssize_t bufsize = 0; // have getline allocate a buffer for us
	if (getline(&line, &bufsize, stdin) == -1) 
	{
		if (feof(stdin)) 
		{
			exit(EXIT_SUCCESS);  // We received an EOF
		} 
		else 
		{
			perror("lsh: getline\n");
			exit(EXIT_FAILURE);
		}
	}
	return line;
}

/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **lsh_parse_commands(char *line)
{
	char ** commands = lsh_split_line(line, LSH_PIPE_DELIM);
	char* command;
	for (int commands_count = 0; commands[commands_count] != NULL; commands_count++)
		commands[commands_count] = trim_str(commands[commands_count]);

	return commands;
}

char **lsh_parse_one_command(char *command)
{
	return lsh_split_line(command, LSH_TOK_DELIM);
}

static char **lsh_split_line(char *line, const char *delimiter)
{
	int bufsize = LSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;

	if (!tokens) 
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, delimiter);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize) 
		{
			bufsize += LSH_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) 
			{
				free(tokens_backup);
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, delimiter);
	}
	tokens[position] = NULL;
	return tokens;
}