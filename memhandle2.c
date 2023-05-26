/**
 * checkOnlySpaces - check if only spaces
 * @line: data holder
 * Return: 1 (not spaces) | 0 (only spaces)
 */
int checkOnlySpaces(char *line)
{
        int i = 0;

        while (line[i])
        {
                if (line[i] != ' ')
                        return (1);
                i++;
        }
        return (0);
}
