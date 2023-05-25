#include "headers.h"

/**
 * int_to_str - convert int to string
 * @num: int value
 * @str: string variable
 *
 * Return: void
 */
void int_to_str(int num, char *str)
{
	int i = 0;
	int neg = 0;
	int j = 0;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return;
	}
	if (num < 0)
	{
		neg = 1;
		num = -num;
	}
	while (num != 0)
	{
		int digit = num % 10;

		str[i++] = digit + '0';
		num /= 10;
	}
	if (neg)
	{
		str[i++] = '-';
	}
	str[i] = '\0';
	i--;

	while (j < i)
	{
		char temp = str[j];

		str[j] = str[i];
		str[i] = temp;
		j++;
		i--;
	}
}

