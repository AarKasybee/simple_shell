#include "shell.h"
/**
 * opSep - separate the operator with spaces
 * @data: data holding the string
 * Return: new separated line | if none return same string
 */
char *opSep(data_t *data)
{
	int i, j, len, newlen, opCount = 0, jmp;
	char op[] = {'|', '&', ';', '$'}, *nline, *line = data->lineptr;

	len = _strlen(line);
	for (j = 0; j < 4; j++)
	{
		for (i = 0; line[i]; i++)
		{
			if (j < 2 && line[i] == op[j] && line[i + 1] == op[j])
				opCount++;
			if (j >= 2 && line[i] == op[j])
			{
				if (op[j] == '$')
					i++;
				opCount++;
			}
		}
	}

	if (opCount == 0)
		return (line);

	newlen = len + opCount * 2;
	nline = malloc(sizeof(char) * (newlen + 1));

	for (i = 0, jmp = 0; i < len; i++)
	{
		opChar(line, nline, &i, &jmp);

		if (line[i] == op[3])
			specialChar(line, nline, &i, &jmp);

		nline[i + jmp] = line[i];
	}
	nline[i + jmp] = '\0';
	free(line);
	return (nline);
}
/**
 * opChar - separate && || and ; with spaces
 * @line: command buffer
 * @nline: new buffer
 * @idx: index
 * @jmp: fix the nline index
 */
void opChar(char *line, char *nline, int *idx, int *jmp)
{
	int i = *idx, j = *jmp;

	while (line[i] == '|' && line[i + 1] == '|')
	{
		nline[i + (j++)] = ' ';
		nline[(i++) + j] = '|';
		nline[(i++) + j] = '|';
		nline[i + (j++)] = ' ';
	}

	while (line[i] == '&' && line[i + 1] == '&')
	{
		nline[i + (j++)] = ' ';
		nline[(i++) + j] = '&';
		nline[(i++) + j] = '&';
		nline[i + (j++)] = ' ';
	}

	while (line[i] == ';')
	{
		nline[i + (j++)] = ' ';
		nline[(i++) + j] = ';';
		nline[i + (j++)] = ' ';
	}

	*idx = i;
	*jmp = j;
}
/**
 * specialChar - separate special char and the variable with spaces
 * @line: command buffer
 * @nline: new buffer
 * @idx: buffer index
 * @jmp: fix the nline index
 */
void specialChar(char *line, char *nline, int *idx, int *jmp)
{
	int i = *idx, j = *jmp;

	nline[i + (j++)] = ' ';

	if (line[i + 1] == '$')
	{
		nline[(i++) + j] = '$';
		nline[(i++) + j] = '$';
	}
	else if (line[i + 1] == '?')
	{
		nline[(i++) + j] = '$';
		nline[(i++) + j] = '?';
	}
	else
	{
		while (line[i] != ' ' && line[i] != '\n' && line[i] != '&' &&
		       line[i] != '|' && line[i] != ';' && line[i] != '$' &&
		       line[i] != '\0')
		{
			nline[i + j] = line[i];
			i++;
		}
	}

	nline[i + (j++)] = ' ';
	*idx = i;
	*jmp = j;
}
/**
 * commentHandler - handles the comment sign
 * @data: data holder
 */
void commentHandler(data_t *data)
{
	int i = 0;

	if (data->lineptr[0] == '#')
	{
		data->lineptr[0] = '\0';
		return;
	}

	while (data->lineptr[i] != '\0')
	{
		if (data->lineptr[i] == '#' && data->lineptr[i - 1] == ' ')
		{
			data->lineptr[i] = '\0';
			return;
		}
		i++;
	}
}

