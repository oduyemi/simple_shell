#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *bf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	bf = malloc(sizeof(char) * (_stlen(dir) + _stlen(HIST_FILE) + 2));
	if (!bf)
		return (NULL);
	bf[0] = 0;
	_stcpy(bf, dir);
	_stcat(bf, "/");
	_stcat(bf, HIST_FILE);
	return (bf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->st, fd);
		_putfd('\n', fd);
	}
	_putfd(BF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *bf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bf = malloc(sizeof(char) * (fsize + 1));
	if (!bf)
		return (0);
	rdlen = read(fd, bf, fsize);
	bf[fsize] = 0;
	if (rdlen <= 0)
		return (free(bf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (bf[i] == '\n')
		{
			bf[i] = 0;
			build_history_list(info, bf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, bf + last, linecount++);
	free(bf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @bf: bffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *bf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, bf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
