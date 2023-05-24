#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _strtok - strtok look-alike function
 * @str: string path value that should be tokenized
 * @delim: delimiter
 *
 * Return: string character
 */
char *_strtok(char *str, const char *delim)
{
	static char *str_cpy; /* maintain state */
	char *str_out = NULL;
	int i, j;

	if (delim == NULL || *delim == '\0')
	{
		perror("Invalid delimiter");
		return (NULL);
	}

	if (str != NULL)
	{
		size_t str_len = _strlen(str);

		str_cpy = malloc((str_len + 1) * sizeof(char));
		if (str_cpy == NULL)
		{
			/* memory allocation failure */
			perror("Memory allocation failed");
			return (NULL);
		}

		i = 0;
		while (str[i] != '\0')
		{
			str_cpy[i] = str[i];
			i++;
		}
		str_cpy[i] = '\0';
	}

	j = 0;
	if (str_cpy != NULL)
	{
		while (str_cpy[j] != '\0')
		{
			if (str_cpy[j] == *delim)
			{
				str_cpy[j] = '\0'; /* replace delimiter with null terminator */

				/* handle empty token case */
				if (j > 0)
				{
					str_out = malloc((j + 1) * sizeof(char));
					if (str_out == NULL)
					{
						perror("Memory allocation failed");
						/*free(str_cpy);  free allocated memory before returning */
						return (NULL);
					}

					for (i = 0; i < j; i++)
						str_out[i] = str_cpy[i];
					str_out[j] = '\0';
				}

				str_cpy += j + 1; /* move to the next character after the delimiter */
				/*free(str_cpy);  free allocated memory before returning */
				return (str_out);
			}
			j++;
		}

		/* handle last token */
		if (j > 0)
		{
			str_out = malloc((j + 1) * sizeof(char));
			if (str_out == NULL)
			{
				perror("Memory allocation failed");
				/*free(str_cpy);  free allocated memory before returning */
				return (NULL);
			}

			for (i = 0; i < j; i++)
				str_out[i] = str_cpy[i];
			str_out[j] = '\0';
		}

		str_cpy += j;
	}

	/*free(str_out);  free allocated memory when str_out is no longer needed */
	/*free(str_cpy);  free allocated memory when the copy is no longer needed */
	return (str_out);
}
