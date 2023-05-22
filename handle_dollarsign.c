#include "main.h"

/**
 * handle_dollarsign - handle variable replacement
 * @cmd: array of shell arguments
 * @cmd_argc: number of arguments
 * @ext_stat: exit status
 *
 * Return: pointer to the modified command
 */
char **handle_dollarsign(char **cmd, size_t cmd_argc, size_t *ext_stat)
{
	size_t i;
	int j, k;
	char tmp[100], *tofree, containdollarsign;

	for (i = 0; i < cmd_argc; i++)
	{
		containdollarsign = 0;
		for (j = 0; j < _strlen(cmd[i]); j++)
		{
			if (cmd[i][j] == '$' && cmd[i][j + 1])
			{
				containdollarsign = 1;
				if (cmd[i][j + 1] == '?')
				{
					free(cmd[i]);
					cmd[i] = _strdup(my_itoa(*ext_stat, tmp, 10));
				}
				else if (cmd[i][j + 1] == '$')
				{
					free(cmd[i]);
					my_itoa(getpid(), tmp, 10);
					cmd[i] = _strdup(tmp);
				}
				else
				{
					for (k = 0; k < _strlen(cmd[i]); k++)
						cmd[i][k] = cmd[i][k + 1];
					tofree = cmd[i];
					cmd[i] = _strdup(_getenv(cmd[i]));
					free(tofree);
				}
			}
		}
		if (!containdollarsign)
		{
			tofree = cmd[i];
			cmd[i] = _strdup(cmd[i]), free(tofree);
		}
	}
	return (cmd);
}
