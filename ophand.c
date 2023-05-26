/**
 * separate_operator - Separate the operator with spaces
 * @data: Data holding the string
 * Return: New separated line | If none, return the same string
 */
char *separate_operator(data_t *data)
{
	int i, j, len, newlen, opCount = 0, jmp;
	char operators[] = {'|', '&', ';', '$'}, *newLine, *line = data->lineptr;

	len = _strlen(line);
	for (j = 0; j < 4; j++)
		for (i = 0; line[i]; i++)
		{
			if (j < 2 && line[i] == operators[j] && line[i + 1] == operators[j])
				opCount++;
			if (j >= 2 && line[i] == operators[j])
			{
				if (operators[j] == '$')
					i++;
				opCount++;
			}
		}
	if (opCount == 0)
		return (line);
	newlen = len + opCount * 2;
	newLine = malloc(sizeof(char) * (newlen + 1));

	for (i = 0, jmp = 0; i < len; i++)
	{
		separate_char(line, newLine, &i, &jmp);

		if (line[i] == operators[3])
			special_char(line, newLine, &i, &jmp);

		newLine[i + jmp] = line[i];
	}
	newLine[i + jmp] = '\0';
	free(line);
	return (newLine);
}

/**
 * separate_char - Separate &&, ||, and ; with spaces
 * @line: Command buffer
 * @newLine: New buffer
 * @idx: Index
 * @jmp: Fix the newLine index
 */
void separate_char(char *line, char *newLine, int *idx, int *jmp)
{
	int i = *idx, j = *jmp;

	if (line[i] == '|' && line[i + 1] == '|')
	{
		newLine[i + (j++)] = ' ', newLine[(i++) + j] = '|';
		newLine[(i++) + j] = '|', newLine[i + (j++)] = ' ';
	}
	if (line[i] == '&' && line[i + 1] == '&')
	{
		newLine[i + (j++)] = ' ', newLine[(i++) + j] = '&';
		newLine[(i++) + j] = '&', newLine[i + (j++)] = ' ';
	}
	if (line[i] == ';')
	{
		newLine[i + (j++)] = ' ', newLine[(i++) + j] = ';';
		newLine[i + (j++)] = ' ';
	}
	*idx = i;
	*jmp = j;
}

/**
 * special_char - Separate special char and the variable with spaces
 * @line: Command buffer
 * @newLine: New buffer
 * @idx: Buffer index
 * @jmp: Fix the newLine index
 */
void special_char(char *line, char *newLine, int *idx, int *jmp)
{
	int i = *idx, j = *jmp;

	newLine[i + (j++)] = ' ';
	if (line[i + 1] == '$')
	{
		newLine[(i++) + j] = '$';
		newLine[(i++) + j] = '$';
	}
	else if (line[i + 1] == '?')
	{
		newLine[(i++) + j] = '$';
		newLine[(i++) + j] = '?';
	}
	else
	{
		for (; line[i] != ' ' && line[i] != '\n' && line[i] != '&'
			     && line[i] != '|' && line[i] != ';'
			     && line[i] != '$' && line[i] != '\0'; i++)
		{
			newLine[i + j] = line[i];
		}
	}
	newLine[i + (j++)] = ' ';
	*idx = i;
	*jmp = j;
}

/**
 * comment_handler - Handles the comment sign
 * @data: Data holder
 */
void comment_handler(data_t *data)
{
	int i;

	if (data->lineptr[0] == '#')
	{
		data->lineptr[0] = '\0';
		return;
	}
	for (i = 1; data->lineptr[i] != '\0'; i++)
	{
		if (data->lineptr[i] == '#' && data->lineptr[i - 1] == ' ')
		{
			data->lineptr[i] = '\0';
			return;
		}
	}
}

