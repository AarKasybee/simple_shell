#include "shell.h"


/**
 * _puts - print a string followed by a line
 * @s: pointer to a string
 * @stream: stream
 */
void _puts(char *s, int stream)
{
	write(stream, s, _strlen(s));
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _strlen - calculate the length of a string
 * this function uses recursion.
 * @s: string
 * Return: string length
 */
int _strlen(const char *s)
{
	int j = 0;

	for (j = 0; s[j] != '\0'; j++)
		;

	return (j);
}
/**
 * print_int - print an integer
 * @n: number
 * @stream: stream
 */
void print_int(int n, int stream)
{
	char buffer[20];
	int i = 0;
	int is_negative = n < 0;

	if (is_negative)
		n = -n;
	do {
		buffer[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (is_negative)
		buffer[i++] = '-';
	while (i > 0) {
		switch (stream) {
			case 1:
				putchar(buffer[--i]);
				break;
			case 2:
				fputc(buffer[--i], stderr);
				break;
			default:
				write(stream, &buffer[--i], 1);
				break;
		}
	}
}

