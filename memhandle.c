#include "shell.h"

/**
 * _memcpy - copy memory
 * @src: memory area to copy
 * @dest: memory arae destination
 * @n: number of bytes to copy
 * Return: pointer to memory @dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}
/**
 * _realloc - reallocate a memory block
 * @ptr: prev pointer
 * @old_size: prev size
 * @new_size: new size
 * Return: new pointer | NULL (failed)
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
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
		i = 0;
		while (i < min)
		{
			p[i] = cp[i];
			i++;
		}
		free(ptr);
	}

	return (p);
}
/**
 * _strdup - copy a string in a new pointer
 * @str: string to copy
 * Return: pointer to string | NULL (failed)
 */
char *_strdup(char *str)
{
	int i = 0, len;
	char *dup;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}

	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';

	return (dup);
}
/**
 * freeData - free the data
 * @data: data holder
 */
void freeData(data_t *data)
{
	/** free data->cmd **/
	freeSarray(data->cmd, data->cmdSize);
	data->cmd = NULL;

	/** free data->lineptr*/
	free(data->lineptr);
	data->lineptr = NULL;

	/* free envi */
	freeSarray(data->envp, 64);
	data->envp = NULL;

	/* free aliases */
	freeSarray(data->alias, 24);
}
/**
 * freeSarray - Free string of arrays
 * @arr: array
 * @size: size of array
 */
void freeSarray(char **arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}

