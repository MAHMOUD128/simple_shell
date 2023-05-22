#include "main.h"

/**
  * print_aliases - prints a list of all aliases
  * @aliases: array of aliases
  */
void print_aliases(char **aliases)
{
	int i;

	for (i = 0; aliases[i]; ++i)
	{
		write(STDOUT_FILENO, aliases[i], _strlen(aliases[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
  * new_definition - checks for '='
  * @str: shell arg
  *
  * Return: index of '=', 0 if not found
  */
size_t new_definition(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '=')
		{
			return (i);
		}
	}
	return (0);
}

/**
  * defined_alias - checks if alias is defined
  * @str: shell arg
  * @aliases: array of aliases
  * @len: len of (arg + '=')
  *
  * Return: index of alias, -1 if it is not defined
  */
int defined_alias(char *str, char **aliases, size_t len)
{
	int index;

	for (index = 0; aliases[index]; index++)
	{
		if (!_strncmp(str, aliases[index], len))
		{
			return (index);
		}
	}
	return (-1);
}

/**
  * check_alias - checks if arguments exists in aliases
  * @arg: array of shell command arguments
  * @aliases: array of aliases
  *
  * Return: 0 if success, 1 otherwise
  */
char check_alias(char *arg, char **aliases)
{
	char exit_status = 0, *alias;
	size_t len;

	if (!new_definition(arg))
	{
		len = _strlen(arg) + 1;
		alias = malloc(len + 1);
		if (!alias)
			return (1);
		_strcpy(alias, arg);
		_strcat(alias, "=");
		if (defined_alias(alias, aliases, len) == -1)
		{
			write(STDOUT_FILENO, "alias: ", 7);
			write(STDOUT_FILENO, arg, len - 1);
			write(STDOUT_FILENO, " not found\n", 11);
			exit_status = 1;
		}
		free(alias);
	}
	return (exit_status);
}

/**
  * shell_alias - defines alias
  * @argv: array of str of shell commands
  * @aliases: array of aliases
  *
  * Return: exit status
  */
size_t shell_alias(char **argv, char **aliases)
{
	size_t exit_status = 0, i, len, argc;
	char *defined_arg;

	if (!argv[1])
		print_aliases(aliases);
	else
	{
		for (argc = 1; argv[argc]; argc++)
			;
		defined_arg = malloc(sizeof(char) * argc);
		if (!defined_arg)
			return (1);
		for (i = 1; argv[i]; i++)
		{
			len = new_definition(argv[i]);
			if (len)
			{
				if (setalias(argv[i], aliases, len))
				{
					free(defined_arg);
					return (1);
				}
				defined_arg[i] = 0;
			}
			else
			{
				defined_arg[i] = check_alias(argv[i], aliases) ? 0 : 1;
				exit_status = !defined_arg[i] ? 1 : exit_status;
			}
		}
		for (i = 1; argv[i]; i++)
			if (!new_definition(argv[i]) && defined_arg[i])
				if (print_alias(argv[i], aliases))
				{
					free(defined_arg);
					return (1);
				}
		free(defined_arg);
	}
	return (exit_status);
}
