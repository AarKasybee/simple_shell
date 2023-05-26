/**
 * _mem_copy - Copy memory
 * @src: Memory area to copy
 * @dest: Memory area destination
 * @n: Number of bytes to copy
 * Return: Pointer to memory @dest
 */
char *_mem_copy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _reallocate - Reallocate a memory block
 * @ptr: Previous pointer
 * @old_size: Previous size
 * @new_size: New size
 * Return: New pointer | NULL (failed)
 */
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p, *cp = ptr;
	unsigned int i, min;

	if (old_size == new_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	min = old_size < new_size ? old_size : new_size;

	p = malloc(new_size);
	if (p == NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size != old_size && ptr != NULL)
	{
		for (i = 0; i < min; i++)
			p[i] = cp[i];
		free(ptr);
	}

	return (p);
}

/**
 * _str_duplicate - Copy a string in a new pointer
 * @str: String to copy
 * Return: Pointer to string | NULL (failed)
 */
char *_str_duplicate(char *str)
{
	int i, len;
	char *dup;

	if (str == NULL)
		return (NULL);

	len = _string_length(str);
	dup = malloc(sizeof(char) * len + 1);
	if (dup == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	for (i = 0; i < _string_length(str); i++)
		dup[i] = str[i];
	dup[i] = '\0';

	return (dup);
}

/**
 * free_data - Free the data
 * @data: Data holder
 */
void free_data(data_t *data)
{
	/** Free data->cmd **/
	free_string_array(data->cmd, data->cmd_size);
	data->cmd = NULL;

	/** Free data->lineptr */
	free(data->lineptr);
	data->lineptr = NULL;

	/* Free environment */
	free_string_array(data->envp, 64);
	data->envp = NULL;

	/* Free aliases */
	free_string_array(data->alias, 24);
}

/**
 * free_string_array - Free array of strings
 * @arr: Array
 * @size: Size of array
 */
void free_string_array(char **arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}

