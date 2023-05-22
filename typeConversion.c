#include "main.h"

/**
 * my_itoa - integer to ascii
 * @i: the integer
 * @strout: output string
 * @base: base
 *
 * Return: A pointer to the output string.
 */

char *my_itoa(long int i, char *strout, int base)
{
	int digit, sign = 0, j = 0;
	unsigned long num = i;

	if (i == 0)
	{
		strout[j++] = '0';
		strout[j] = '\0';
		return (strout);
	}

	if (i < 0)
	{
		sign = 1;
		num = -i;
	}

	while (num != 0)
	{
		digit = num % base;
		strout[j++] = (digit > 9) ? ('a' + digit - 10) : ('0' + digit);
		num = num / base;
	}

	if (sign == 1)
	{
		strout[j] = '-';
		j++;
	}

	strout[j] = '\0';

	_strrev(strout);
	return (strout);
}

/**
  * _atoi - convert str to int
  * @s: str to be converted
  * @status: pointer to status variable
  *
  * Return: int
  */
int _atoi(char *s, char *status)
{
	char sign = 1;
	unsigned int num = 0;

	while (*s != '\0')
	{
		if (*s == '-')
		{
			sign *= -1;
		}
		else if (*s >= '0' && *s <= '9')
		{
			num = num * 10 + *s - '0';
		}
		else if (*s != '+')
		{
			*status = -1;
			return (0);
		}
		s++;
	}
	*status = 0;
	return (sign * num);
}
