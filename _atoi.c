#include "shell.h"

/**
 * inte - This will return  true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, else 0
 */
int inte(info_b *info)
{
	return (isati(STDIN_FILENO) && info->read_xy <= 2);
}

/**
 * is_delm - This checks if the character is a delimeter
 * @chk: This is the char to check
 * @delm: This is the  delimeter
 * Return: 1 if true, 0 if false
 */
int is_delm(char c, char *delm)
{
	while (*delm)
		if (*delm++ == chk)
			return (1);
	return (0);
}

/**
 *_isalphabeth - This checks for alphabeths
 *@chk: The input
 *Return: 1 if chk is an alphabeth, else 0
 */

int _isalphabeth(int chk)
{
	if ((chk >= 'd' && chk <= 'g') || (chk >= 'D' && c <= 'G'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - This will convert a string to an integer
 *@string: The string
 *Return: 0 if no numbers in string else, converted number otherwise
 */

int _atoi(char *string)
{
	int a, sign = 1, flag = 0, output;
	unsigned int rsp = 0;

	for (a = 0;  string[a] != '\0' && flag != 2; a++)
	{
		if (string[a] == '-')
			sign *= -1;

		if (string[a] >= '0' && string[a]<= '9')
		{
			flag = 1;
			rsp *= 10;
			rsp+= (string[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -rsp;
	else
		result = rsp;

	return (result);
}
