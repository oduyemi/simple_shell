#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathst: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new bffer
 */
char *dup_chars(char *pathst, int start, int stop)
{
	static char bf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathst[i] != ':')
			bf[k++] = pathst[i];
	bf[k] = 0;
	return (bf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathst: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathst, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathst)
		return (NULL);
	if ((_stlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathst[i] || pathst[i] == ':')
		{
			path = dup_chars(pathst, curr_pos, i);
			if (!*path)
				_stcat(path, cmd);
			else
			{
				_stcat(path, "/");
				_stcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathst[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
