#include "main.h"

/**
  * _getenv - gets an evironment variable
  * @name: variable name
  *
  * Return: pointer to str contains variable value
  */
char *_getenv(char *name)
{
	size_t len = _strlen(name);
	char **env;

	for (env = environ; *env != NULL; env++)
		if (!_strncmp(*env, name, len) && (*env)[len] == '=')
			return (&(*env)[len + 1]);
	return (NULL);
}
