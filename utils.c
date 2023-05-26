#include "main.h"

/**
 * _getline - read line from the stream
 * @lptr: pointer to the buffer where to store string
 * @n: pointer to the size of the string
 * @strm: the stream
 */
void _getline(char **restrict lptr, size_t *restrict n, FILE *restrict strm)
{
    ssize_t val = getline(lptr, n, strm);
    if (val == -1)
    {
        handleGetlineError();
    }
}

/**
 * handleGetlineError - handle errors that occur during getline
 */
void handleGetlineError()
{
    if (errno == EINVAL)
    {
        _puts("Error: invalid argument");
    }
    else if (errno == ENOMEM)
    {
        _puts("Error: failed to allocate memory");
    }
}
