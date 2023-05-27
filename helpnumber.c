#include "shell.h"

/**
 * convert_number_to_string - converts a number to a string.
 * @number: number to be converted into a string.
 * @string_buffer: buffer to save the number as a string.
 * @base: base to convert the number.
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string_buffer, int base)
{
	int index = 0, is_negative = 0;
	long quotient = number;
	char conversion_table[] = {"0123456789abcdef"};

	if (quotient == 0)
		string_buffer[index++] = '0';

	if (string_buffer[0] == '-')
		is_negative = 1;

	while (quotient)
	{
		if (quotient < 0)
			string_buffer[index++] = conversion_table[-(quotient % base)];
		else
			string_buffer[index++] = conversion_table[quotient % base];
		quotient /= base;
	}

	if (is_negative)
		string_buffer[index++] = '-';

	string_buffer[index] = '\0';
	reverse_string(string_buffer);
}

/**
 * string_to_integer - convert a string to an integer.
 *
 * @str: pointer to the source string.
 * Return: integer value of the string or 0.
 */
int string_to_integer(char *str)
{
	int sign = 1;
	unsigned int result = 0;

	while (!('0' <= *str && *str <= '9') && *str != '\0')
	{
		if (*str == '-')
			sign *= -1;
		if (*str == '+')
			sign *= +1;
		str++;
	}

	while ('0' <= *str && *str <= '9' && *str != '\0')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}

	return (result * sign);
}

/**
 * count_occurrences - count the occurrences of a character in a string.
 *
 * @str: pointer to the source string.
 * @ch: pointer to the character to be counted.
 * Return: number of occurrences or 0.
 */
int count_occurrences(char *str, char *ch)
{
	int i = 0, count = 0;

	for (; str[i]; i++)
	{
		if (str[i] == ch[0])
			count++;
	}
	return count;
}

