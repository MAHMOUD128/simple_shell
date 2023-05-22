#include "main.h"

/**
  * builtin_exec - executes built in commands
  * @argv: array of str of shell commands
  * @in_count: shell input counter
  * @aliases: array of aliases
  * @prog_name: shell name
  *
  * Return: exit status if command is found and executed, -1 otherwise
  */
ssize_t builtin_exec(char **argv, unsigned long in_count,
		char **aliases, char *prog_name)
{
	com_t coms[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"cd", shell_cd},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
	};
	int i;

	if (!_strncmp("env", argv[0], 3) && argv[1])
		return (-1);
	else if (!_strncmp("alias", argv[0], 5))
		return (shell_alias(argv, aliases));
	for (i = 0; i < 5; i++)
	{
		if (!_strncmp(coms[i].command, argv[0], 8))
		{
			return (coms[i].f(argv, in_count, prog_name));
		}
	}
	return (-1);
}

/**
  * exec - execute programs
  * @argv: array of strings of shell arguments
  * @in_count: shell input counter
  * @aliases: array of aliases
  * @env: array of str
  * @prog_name: shell_name
  *
  * Return: exit status
  */
size_t exec(char **argv, unsigned long in_count, char **aliases,
		char **env, char *prog_name)
{
	pid_t pid = 0, w;
	char *command = NULL, *actual_command = NULL;
	ssize_t builtin_status;
	int status, exit_status;

	builtin_status = builtin_exec(argv, in_count, aliases, prog_name);
	if (builtin_status != -1)
		return (builtin_status);
	command = argv[0];
	actual_command = find_path(command);
	if (actual_command)
		pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		if (!actual_command)
		{
			errorHandler(10, in_count, argv[0], prog_name);
			exit_status = 127;
		}
		else
		{
			execve(actual_command, argv, env);
		}
	}
	else
	{
		do {
			w = wait(&status);
			if (w == -1)
				exit(1);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(actual_command);
	return (exit_status);
}
