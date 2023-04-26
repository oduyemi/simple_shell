#include "shell.h"

/**
 *eputs_ - prints an input string
 * @st: the string to be printed
 *
 * Return: Nothing
 */
void eputs_(char *st)
{
	int i = 0;

	if (!st)
		return;
	while (st[i] != '\0')
	{
		_eputchar(st[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char bf[WRITE_BF_SIZE];

	if (c == BF_FLUSH || i >= WRITE_BF_SIZE)
	{
		write(2, bf, i);
		i = 0;
	}
	if (c != BF_FLUSH)
		bf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char bf[WRITE_BF_SIZE];

	if (c == BF_FLUSH || i >= WRITE_BF_SIZE)
	{
		write(fd, bf, i);
		i = 0;
	}
	if (c != BF_FLUSH)
		bf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
