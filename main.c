#include "main.h"

/**
  * shell_input - gets shell input
  * @lineptr: pointer to the input string
  * @n: size of input buffer
  * @argv: array of main arguments
  *
  * Return: 1 if EOF, 0 otherwise
  */
size_t shell_input(char **lineptr, size_t *n, char **argv)
{
	ssize_t reads;

	if (argv[1])
	{
		int fd;

		*lineptr = malloc(1000);
		if (!*lineptr)
			return (1);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			errorHandler(11, 0, argv[1], argv[0]);
			return (1);
		}
		reads = read(fd, *lineptr, 1000);
		if (reads == -1)
			return (1);
		(*lineptr)[reads] = '\0';
		handle_newline_delim(lineptr);
		close(fd);
	}
	else
	{
		reads = getline(lineptr, n, stdin);
		if (reads == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (1);
		}
		(*lineptr)[reads] = '\0';
	}
	return (0);
}

/**
 * handle_command - handle command for execution
 * @sargv: array of shell arguments
 * @sargc: index of delim after command
 * @command_argc: number of arguments of each command
 * @aliases: array of aliases
 * @ext_stat: exit status
 *
 * Return: command
 */
char **handle_command(char **sargv, size_t sargc, size_t command_argc,
		char **aliases, size_t *ext_stat)
{
	size_t i;
	char **command = malloc(sizeof(char *) * (command_argc + 1));

	if (!command)
		return (NULL);
	for (i = 0; i < command_argc; i++)
		command[i] = _strdup(sargv[sargc - (command_argc) + i]);
	command[i] = NULL;
	command = getalias(command, command_argc, aliases);
	if (!command)
		return (NULL);
	command = handle_dollarsign(command, command_argc, ext_stat);
	if (!command)
		return (NULL);
	return (command);
}

/**
  * m_helper - handle shell input for execution
  * @sargv: array of arguments
  * @inCnt: shell input counter
  * @extStat: exit state
  * @aliases: array of aliases
  * @env: array of str
  * @prog_name: shell name
  *
  * Return: 0 if success, 1 if it fails
  */
char m_helper(char **sargv, unsigned long *inCnt, size_t *extStat,
		char **aliases,  char **env, char *prog_name)
{
	size_t sargc = 0, command_argc, exec_return;
	char **command, last_state = 1, execute_case = 1, is_and = 1;

	if (concat_sep(sargv) != -1)
		errorHandler(6 + concat_sep(sargv), *inCnt, NULL, prog_name), (*inCnt)--;
	else
		while (sargv && sargv[sargc])
		{
			for (command_argc = 0; sargv[sargc] && sargv[sargc][0] != ';'
					&& sargv[sargc][0] != '&' && sargv[sargc][0] != '|'; sargc++)
				command_argc++;
			if (command_argc)
			{
				command = handle_command(sargv, sargc, command_argc, aliases, extStat);
				if (!command)
					return (1);
				if (execute_case)
				{
					exec_return = exec(command, *inCnt, aliases, env, prog_name);
					if (exec_return != 1000)
						*extStat = exec_return;
					else
					{
						free_array(command);
						return (1);
					}
					last_state = (!*extStat) ? 1 : 0;
				}
				else
					last_state = (is_and) ? 0 : 1;
				if (sargv[sargc] && sargv[sargc][0] == '&')
					is_and = 1, execute_case = last_state;
				else if (sargv[sargc] && sargv[sargc][0] == '|')
					is_and = 0, execute_case = (last_state) ? 0 : 1;
				free_array(command);
			}
			if (sargv[sargc])
				sargc++;
		}
	return (0);
}

/**
 * removeComments - remove comments from command
 * @sargv: array of shell arguments
 */
void removeComments(char **sargv)
{
	size_t i = 0, j;

	for (; sargv && sargv[i]; i++)
	{
		if (sargv[i][0] == '#')
		{
			for (j = i; sargv[j]; j++)
				free(sargv[j]);
			sargv[i] = NULL;
			return;
		}
	}
}

/**
  * main - launch the shell
  * @argc: number of arguments
  * @argv: array of arguments
  * @env: array of str
  *
  * Return: 0
  */
int main(int argc, char *argv[], char *env[])
{
	size_t n = 0, exit_status = 0, eof = 0;
	char *lineptr = NULL, **sargv = NULL;
	char  *prompt = "$ ", *delim = " \n";
	unsigned long in_count = 0;
	char **aliases = malloc(sizeof(char *) * 1024);

	aliases[0] = NULL, signal(SIGINT, handle_sigint);
	do {
		if (isatty(STDIN_FILENO) && argc == 1)
			write(STDOUT_FILENO, prompt, 2);
		eof = shell_input(&lineptr, &n, argv);
		if (eof)
		{
			free_modified_var(), free(lineptr);
			free_array(aliases);
			return ((argv[1]) ? 2 : exit_status);
		}
		in_count++, sargv = _strtok(lineptr, delim);
		removeComments(sargv);
		if (m_helper(sargv, &in_count, &exit_status, aliases, env, argv[0]))
		{
			free_modified_var(), free_array(sargv);
			free(lineptr), free_array(aliases);
			return (exit_status);
		}
		free_array(sargv);
		if (exit_status >= 256)
		{
			free_modified_var(), free(lineptr);
			free_array(aliases);
			return (exit_status - 256);
		}
	} while (argc == 1);
	free(lineptr), free_array(aliases);
	free_modified_var();
	return (exit_status);
}
