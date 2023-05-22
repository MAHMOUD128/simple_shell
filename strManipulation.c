#include "main.h"

/**
  * _strlen - computes len of a string
  * @s: string to be checked
  *
  * Return: len of s
  */
int _strlen(char *s)
{
	int i = 0;

	for (; s && *s != '\0'; i++)
	{
		s++;
	}
	return (i);
}

/**
  * _strncmp - compares two strs to n bytes
  * @s1: first str to be compared
  * @s2: second str to be compared
  * @n: num of bytes to be compared
  *
  * Return: corresponding to n, 0 if the s1 & s2 are equal
  * a negative value if s1 is less than s2
  * a positive value if s1 is greater than s2
  */
int _strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 != '\0' && *s2 != '\0' && --n)
	{
		if (*s1 != *s2)
		{
			break;
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
  * _strcat - Concatenates two strings
  * @dest: The destination string
  * @src: The source string
  *
  * Return: A pointer to the resulting string dest
  */
char *_strcat(char *dest, char *src)
{
	int dlen = 0, i;

	while (dest[dlen])
	{
		dlen++;
	}

	for (i = 0; src[i] != 0; i++)
	{
		dest[dlen] = src[i];
		dlen++;
	}

	dest[dlen] = '\0';
	return (dest);
}

/**
 * _strrev - Reverses a string.
 * @str: The string to be reversed.
 *
 * Return: pointer to reversed string
 */
char *_strrev(char *str)
{
	int i,	j = 0;
	char temp;

	while (str[j])
	{
		j++;
	}

	for (i = 0; i < j / 2; i++)
	{
		temp = str[i];
		str[i] = str[j - i - 1];
		str[j - i - 1] = temp;
	}
	return (str);
}

/**
  * _strdup - allocates a new space for a cpy of str
  * @str: str to be copied
  *
  * Return: pointer to new space
  */
char *_strdup(char *str)
{
	if (str != (void *)'\0')
	{
		char *strcpy = str, *strdup, *strdup2;
		int len = 1;

		while (*strcpy != '\0')
		{
			len++;
			strcpy++;
		}
		strdup = (char *)malloc(len * sizeof(char));
		strdup2 = strdup;
		strcpy = str;
		while (strdup != (void *)'\0' && len--)
		{
			*strdup2 = *strcpy;
			strcpy++;
			strdup2++;
		}
		return (strdup);
	}
	else
	{
		return (str);
	}
}
