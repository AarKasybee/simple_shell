#include "shell.h"

/**
 * custom_strtok - Tokenize a string
 * @str: String
 * @delim: Delimiter
 * @size: Size
 * Return: Array of tokens
 */
char **custom_strtok(char *str, const char *delim, int *size)
{
	char **token_arr;
	int i, j = 0, k, token_len = 0;

	if (str == NULL || delim == NULL || str[0] == '\0')
		return (NULL);

	*size = countTokens(str, delim);
	if (*size == 0)
		return (NULL);

	token_arr = malloc(sizeof(char *) * (*size + 1));
	if (token_arr == NULL)
		return (NULL);

	for (i = 0; i < *size; i++)
	{
		while (isDelimiter(str[j], delim))
			j++;

		token_len = getTokenLength(str, delim, j);
		token_arr[i] = malloc(sizeof(char) * (token_len + 1));
		if (token_arr[i] == NULL)
		{
			freeTokenArray(token_arr, *size);
			return (NULL);
		}

		for (k = 0; k < token_len; k++)
		{
			token_arr[i][k] = str[j];
			j++;
		}
		token_arr[i][k] = '\0';
	}

	token_arr[i] = NULL;
	return (token_arr);
}

/**
 * countTokens - Count the number of tokens
 * @str: Tokens holder
 * @delim: Delimiter
 * Return: Number of tokens
 */
int countTokens(char *str, const char *delim)
{
	int i, count = 0;

	if (str == NULL || delim == NULL)
		return (0);

	for (i = 0; i < custom_strlen(str); i++)
	{
		if (!isDelimiter(str[i], delim))
		{
			count++;
			i += getTokenLength(str, delim, i);
		}
	}

	return (count);
}

/**
 * getTokenLength - Calculate the length of a token
 * @str: String
 * @delim: Delimiter
 * @index: Index
 * Return: Integer
 */
int getTokenLength(char *str, const char *delim, int index)
{
	int length;

	for (length = 0; str[index + length] && str[index + length] != '\n'; length++)
	{
		if (isDelimiter(str[index + length], delim))
			break;
	}

	return (length);
}

/**
 * isDelimiter - Check if the character is a delimiter
 * @c: Character to check
 * @delim: Delimiter(s)
 * Return: 1 (is delimiter) | 0 (not delimiter)
 */
int isDelimiter(char c, const char *delim)
{
	int i;

	for (i = 0; i < custom_strlen(delim); i++)
	{
		if (c == delim[i])
			return (1);
	}

	return (0);
}

