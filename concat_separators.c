#include "main.h"

/**
  * concat_sep - checks for 2 following separators
  * @sargv: array of args
  *
  * Return: 0 for ';' case, 1 for ';;' case,
  * 2 for unexpected &&, 3 for unexpected ||, -1 otherwise
  */
ssize_t concat_sep(char **sargv)
{
	int i, j;

	for (i = 0; sargv && sargv[i]; i++)
	{
		for (j = 1; sargv[i][j]; j++)
		{
			if (sargv[i][j] == ';' && sargv[i][j - 1] == ';')
				return (1);
			else if (sargv[i][j] == '&' && sargv[i][j - 1] == '&'
					&& j == 2)
				return (2);
			else if (sargv[i][j] == '|' && sargv[i][j - 1] == '|'
					&& j == 2)
				return (3);
		}
		if (i && sargv[i][0] == ';' && sargv[i - 1][0] == ';')
			return (0);
		else if (i && sargv[i][0] == '&' && sargv[i - 1][0] == '&')
			return (2);
		else if (i && sargv[i][0] == '|' && sargv[i - 1][0] == '|')
			return (3);
		else if (i == 0 && sargv[0][0] == ';')
			return (0);
		else if (i == 0 && sargv[0][0] == '&')
			return (2);
		else if (i == 0 && sargv[0][0] == '|')
			return (3);
	}
	return (-1);
}
