#include "shell.h"

/**
 * _stlen - this will return the length of a string
 * @string: the string to check it's length
 *
 * Return: int of string length
 */
int _stlen(char *string)
{
	int s = 0;

	if (!string)
		return (0);

	while (*string++)
		s++;
	return (s);
}

/**
 * _stcmp - this will perform comparison of two strangs.
 * @string1: this is the first string
 * @string2: this is the second string
 *
 * Return: negative if string1 < string2, positive if string1 > string2, zero if string1 == string2
 */
int _stcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * startswith - checks if needle starts with haystack
 * @hay_stack: string to search
 * @ndl: the substring to find
 *
 * Return: address of next char of hay_stack or NULL
 */
char *startswith(const char *hay_stack, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hay_stack++)
			return (NULL);
	return ((char *)hay_stack);
}

/**
 * _stcat - it will concatenate two strings
 * @dst: destination buffer
 * @bf_src: this is the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_stcat(char *dst, char *bf_src)
{
	char *rt = dst;

	while (*dst)
		dst++;
	while (*bf_src)
		*dst++ = *bf_src++;
	*dst = *bf_src;
	return (rt);
}
