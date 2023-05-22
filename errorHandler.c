#include "main.h"

/**
  * separatorsCases - detect separator errors
  * @errnum: error case
  * @error_msg: error message
  */
void separatorsCases(char errnum, char **error_msg)
{
	switch (errnum)
	{
		case 6:
			*error_msg = ": Syntax error: \";\" unexpected"
			;
			break;
		case 7:
			*error_msg = malloc(sizeof(char) * 32);
			_strcpy(*error_msg, ": Syntax error: \";")
			;
			_strcat(*error_msg, ";\" unexpected")
			;
			break;
		case 8:
			*error_msg = ": Syntax error: \"&&\" unexpected";
			break;
		case 9:
			*error_msg = ": Syntax error: \"||\" unexpected";
	}
}
/**
  * err_helper - detect error case
  * @errnum: error case
  * @error_msg: error message
  * @msg_len: len of message
  */
void err_helper(char errnum, char **error_msg, size_t *msg_len)
{
	if (errnum >= 6 && errnum <= 9)
		separatorsCases(errnum, error_msg);
	switch (errnum)
	{
		case 0:
			*error_msg = ": exit: Illegal number: ";
			break;
		case 1:
			*error_msg = ": cd: can't cd to ";
			break;
		case 2:
			*error_msg = ": setenv: too few arguments";
			break;
		case 3:
			*error_msg = ": setenv: Invalid argument: ";
			break;
		case 4:
			*error_msg = ": unsetenv: too few arguments";
			break;
		case 5:
			*error_msg = ": unsetenv: Invalid argument: ";
			break;
		case 10:
			*error_msg = ": not found";
			break;
		case 11:
			*error_msg = ": cannot open ";
	}
	*msg_len = _strlen(*error_msg);
}

/**
 * errorHandler - prints errors to STDERR
 * @errnum: error case
 * @in_count: shell input counter
 * @farg: command first argument
 * @prog_name: shell name
 */

void errorHandler(char errnum, unsigned int in_count,
		char *farg, char *prog_name)
{
	char *error_msg, *shell_err, buff[100];
	size_t msg_len = 0, len = 0;

	err_helper(errnum, &error_msg, &msg_len);
	len = msg_len + _strlen(prog_name)
		       + _strlen(my_itoa(in_count, buff, 10))
		       + _strlen(farg) + 3;
	len += (errnum == 10) ? 2 : (errnum == 11) ? 14 : 0;
	shell_err = malloc(len + 1);
	_strcpy(shell_err, prog_name), _strcat(shell_err, ": ");
	_strcat(shell_err, buff);
	if (errnum == 10)
	{
		_strcat(shell_err, ": ");
		_strcat(shell_err, farg);
	}
	_strcat(shell_err, error_msg);
	if (farg && errnum != 10)
		_strcat(shell_err, farg);
	if (errnum == 11)
		_strcat(shell_err, ": No such file");
	_strcat(shell_err, "\n");
	write(STDERR_FILENO, shell_err, len), free(shell_err);
	if (errnum == 7)
		free(error_msg);
}
