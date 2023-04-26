#include "shell.h"

/**
 * **sttow - splits a string into words. Repeat delimiters are ignored
 * @st: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **sttow(char *st, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; st[i] != '\0'; i++)
		if (!is_delim(st[i], d) && (is_delim(st[i + 1], d) || !st[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(st[i], d))
			i++;
		k = 0;
		while (!is_delim(st[i + k], d) && st[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **sttow2 - splits a string into words
 * @st: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **sttow2(char *st, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != d && st[i + 1] == d) ||
		    (st[i] != d && !st[i + 1]) || st[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (st[i] == d && st[i] != d)
			i++;
		k = 0;
		while (st[i + k] != d && st[i + k] && st[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
