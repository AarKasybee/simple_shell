#include "main.h"

void read_stream(int c, ssize_t chars_read, size_t bytes_allocated,
		size_t *n, char **lineptr);

/**
 * _getline - reads an entire line from stream, storing the address
 *  of the buffer containing the text into *lineptr.  The buffer is
 *  null-terminated and includes the newline character, if one was found.
 *
 *  @lineptr: stores g the address of the buffer containing the text
 *  @n: number of bytes allocated to the buffer
 *  @stream:user input stream from the terminal
 *
 *  Return: the number of char read
 */
ssize_t _getline(char **restrict lineptr, size_t *restrict n,
		FILE * restrict stream)
{
	ssize_t chars_read = 0; /* keeps track of the num of char read */
	size_t bytes_allocated = *n;
	int c;

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		return (-1); /* Invalid input */
	}

	/* Allocate memory for the line buffer if needed*/
	if (*lineptr == NULL || bytes_allocated == 0)
	{
		bytes_allocated = 128; /* Initial buffer size */
		*lineptr = malloc(bytes_allocated);
		if (*lineptr == NULL)
		{
			return (-1); /* Memory allocation failed */
		}
	}
	/* Read characters from stream until newline or end of file */
	read_stream(c, chars_read, bytes_allocated, n, lineptr);

	if (chars_read == 0)
	{
		return (-1); /* End of file reached before any characters were read */
	}

	/* Null-terminate the line */
	(*lineptr)[chars_read] = '\0';
	return (chars_read);
}

/**
 * read_stream - function reads characters
 * @c: int - number of characters
 * @chars_read: keeps track of the num of char read
 * @bytes_allocated: same as n
 * @lineptr:  stores g the address of the buffer containing the text
 * @n:  number of bytes allocated to the buffer
 */
void read_stream(int c, ssize_t chars_read, size_t bytes_allocated,
		size_t *n, char **lineptr)
{
	while ((c = fgetc(stream)) != EOF)
	{
		if (chars_read + 1 >= bytes_allocated)
		{
			/* Expand the buffer if needed */
			bytes_allocated *= 2;
			char *new_lineptr = realloc(*lineptr, bytes_allocated);

			if (new_lineptr == NULL)
			{
				return (-1); /* Memory allocation failed */
			}
			*lineptr = new_lineptr;
			*n = bytes_allocated;
		}
		(*lineptr)[chars_read++] = c;
		if (c == '\n')
		{
			break; /* End of line found */
		}
	}
}
