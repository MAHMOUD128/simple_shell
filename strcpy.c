#include "main.h"

/**
  * _strcpy - copies str pointed to by src to dest
  * @dest: pointer to buffer
  * @src: pointer to str to be copied
  *
  * Return: pointer to dest
  */
char *_strcpy(char *dest, char *src)
{
	char *destcpy = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (destcpy);
}

/**
  * _strncpy - copies a string
  * @dest: pointer to destination
  * @src: str to be copied
  * @n: bytes to be copied
  *
  * Return: pointer to dest
  */
char *_strncpy(char *dest, char *src, int n)
{
	char *destcpy = dest;

	while (n--)
	{
		if (*src != '\0')
		{
			*destcpy = *src;
			src++;
		}
		else
		{
			*destcpy = '\0';
		}
		destcpy++;
	}
	return (dest);
}
