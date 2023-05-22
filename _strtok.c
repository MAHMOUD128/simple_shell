#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
  * isdelim - checks if char one of set of delimiter
  * @c: char to be checked
  * @delim: str of delimiters
  *
  * Return: 1 if it is delimiter, 2 if the delim is ';',
  * 3 if delim is '&', 4 if delim is '|', 0 otherwise
  */
char isdelim(char c, char *delim)
{
	int i;

	for (i = 0; delim[i]; i++)
		if (delim[i] == c)
			return (1);
		else if (';' == c)
			return (2);
		else if ('&' == c)
			return (3);
		else if ('|' == c)
			return (4);
	return (0);
}

/**
  * wordsCounter - count words in str
  * @str: str to be computed
  * @delim: tokens seperators
  *
  * Return: num of words
  */
int wordsCounter(char *str, char *delim)
{
	int words = 0, i = 0;
	char one_arg = -1;

	if (isdelim(str[0], delim) != 1)
		words++;
	if (str[0] == '\'')
		one_arg = 1;
	for (i = 1; str[i]; i++)
	{
		if (one_arg == -1)
		{
			if (isdelim(str[i - 1], delim) && !isdelim(str[i], delim))
				words++;
			else if (isdelim(str[i - 1], delim) != 2 && isdelim(str[i], delim) == 2)
				words++;
			else if (isdelim(str[i - 1], delim) != 3 && isdelim(str[i], delim) == 3)
				words++;
			else if (isdelim(str[i - 1], delim) != 4 && isdelim(str[i], delim) == 4)
				words++;
		}
		if (str[i] == '\'')
			one_arg *= -1;
	}
	return (words);
}

/**
  * free_array - free allocated array
  * @array: pointer to pointer of char
  */
void free_array(char **array)
{
	int i = 0;

	while (array && array[i])
		free(array[i++]);
	free(array);
}

/**
  * toklen - calculate token length
  * @strcpy: pointer to the start of the token
  * @delim: string delimter
  *
  * Return: the token length
  */
int toklen(char *strcpy, char *delim)
{
	int len = 0;

	if (isdelim(*strcpy, delim) == 0)
	{
		if (*strcpy == '\'')
		{
			len = 1;
			while (strcpy[len] != '\'')
				len++;
			len++;
		}
		else
			while (isdelim(*(strcpy + len), delim) == 0 && strcpy[len] != '\0')
			{
				if (strcpy[len] == '\'')
				{
					len++;
					while (strcpy[len] != '\'')
						len++;
					len++;
				}
				else
					len++;
			}
	}
	else if (isdelim(*strcpy, delim) == 2)
		while (isdelim(*(strcpy + len), delim) == 2)
			len++;
	else if (isdelim(*strcpy, delim) == 3)
		while (isdelim(*(strcpy + len), delim) == 3)
			len++;
	else if (isdelim(*strcpy, delim) == 4)
		while (isdelim(*(strcpy + len), delim) == 4)
			len++;
	return (len);
}

/**
  * _strtok - splits str into tokens
  * @str: str to be splitted
  * @delim: tokens seperators
  *
  * Return: pointer to array of str, NULL if str = NULL or str = "" or it fails
  */
char **_strtok(char *str, char *delim)
{
	char *strcpy = str, **wordsArray;
	int words = 1, len, wordIndex = 0;

	if (str == (void *)'\0' || *str == '\0')
		return ((void *)'\0');
	words += wordsCounter(str, delim);
	if (words == 1)
		return ((void *)'\0');
	wordsArray = (char **)malloc(words * sizeof(char *));
	if (wordsArray != (void *)'\0')
	{
		strcpy = str;
		while (*strcpy != '\0')
		{
			len = toklen(strcpy, delim);
			if (len)
			{
				wordsArray[wordIndex] = (char *)malloc
					((len + 1) * sizeof(char));
				if (wordsArray[wordIndex] == (void *)'\0')
				{
					free_array(wordsArray);
					return ((void *)'\0');
				}
				_strncpy(wordsArray[wordIndex], strcpy, len);
				strcpy += len - 1;
				wordsArray[wordIndex][len] = '\0', wordIndex++;
			}
			strcpy++;
		}
		wordsArray[wordIndex] = (void *)'\0';
	}
	return (wordsArray);
}
