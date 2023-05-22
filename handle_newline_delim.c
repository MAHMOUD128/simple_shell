#include "main.h"

/**
 * handle_newline_delim - separate commands with ';'
 * @buff: pointer to buffer
 */
void handle_newline_delim(char **buff)
{
	char delimflag = -1;
	size_t i;

	for (i = 0; *buff && (*buff)[i]; i++)
	{
		if (delimflag == 1)
		{
			if ((*buff)[i] == '\n')
			{
				(*buff)[i] = ';';
				delimflag *= -1;
			}
		}
		else if ((*buff)[i] != '\n')
		{
			delimflag *= -1;
		}
	}
}
