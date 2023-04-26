#include "shell.h"

/**
 * _stcpy - this will copy a string
 * @dst: the destination
 * @bf_src: the source
 *
 * Return: pointer to destination
 */
char *_stcpy(char *dst, char *bf_src)
{
	int s = 0;

	if (dst == bf_src || bf_src == 0)
		return (dst);
	while (bf_src[s])
	{
		dst[i] = bf_src[s];
		s++;
	}
	dst[s] = 0;
	return (dst);
}

/**
 * _stdp - this will duplicate a string
 * @st: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_stdp(const char *st)
{
	int st_length = 0;
	char *rt;

	if (st == NULL)
		return (NULL);
	while (*st++)
		st_length++;
	rt = malloc(sizeof(char) * (st_length + 1));
	if (!rt)
		return (NULL);
	for (st_length++; st_length--;)
		rt[st_length] = *--st_length;
	return (rt);
}

/**
 *_puts - prints an input string
 *@st: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *st)
{
	int s = 0;

	if (!s)
		return;
	while (st[s] != '\0')
	{
		_putchar(st[s]);
		s++;
	}
}

/**
 * _putchar - writes the character e to stdout
 * @e: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and err_no is set appropriately.
 */
int _putchar(char e)
{
	static int s;
	static char bf[WRITE_BF_SIZE];

	if (c == BF_FLUSH || s >= WRITE_BF_SIZE)
	{
		write(1, bf, s);
		s = 0;
	}
	if (e != BF_FLUSH)
		bf[s++] = e;
	return (1);
}
