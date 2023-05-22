#include "main.h"

/**
  * create_modified_var - set modified var in environ
  *
  * Return: 0 if success, 1 if it fails
  */
char create_modified_var(void)
{
	size_t size = 0;
	char *modified_vars = malloc(_strlen("DONOT_EDIT=") + 1000);

	if (!modified_vars)
		return (1);
	_strcpy(modified_vars, "DONOT_EDIT=");
	for (; environ[size]; size++)
		;
	environ[size] = modified_vars;
	environ[size + 1] = NULL;
	return (0);
}

/**
  * append_to_modified_vars - append var name to modified vars
  * @name: var name
  */
void append_to_modified_vars(char *name)
{
	_strcat(_strcat(_getenv("DONOT_EDIT"), name), ":");
}

/**
  * check_if_appended - check if var name is modified before
  * @name: var name
  *
  * Return: 1 if appended, 0 otherwise
  */
char check_if_appended(char *name)
{
	char **vars = _strtok(_getenv("DONOT_EDIT"), ":");
	size_t i;

	for (i = 0; vars && vars[i]; i++)
	{
		if (!_strncmp(vars[i], name, _strlen(name)))
		{
			free_array(vars);
			return (1);
		}
	}
	free_array(vars);
	return (0);
}

/**
  * free_modified_var - free modified and new vars
  */
void free_modified_var(void)
{
	char **vars = _strtok(_getenv("DONOT_EDIT"), ":"), *args[2];
	size_t i = 0;

	for (; vars && vars[i]; i++)
	{
		args[1] = vars[i];
		_unsetenv(args, 0, NULL);
	}
	args[1] = "DONOT_EDIT";
	_unsetenv(args, 0, NULL);
	free_array(vars);
}
