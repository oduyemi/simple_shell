#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->arg = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->arg = sttow(info->arg, " \t");
		if (!info->arg)
		{

			info->arg = malloc(sizeof(char *) * 2);
			if (info->arg)
			{
				info->arg[0] = _stdup(info->arg);
				info->arg[1] = NULL;
			}
		}
		for (i = 0; info->arg && info->arg[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->arg);
	info->arg = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_bf)
			free(info->arg);
		if (info->envn)
			free_list(&(info->envn));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_bf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BF_FLUSH);
	}
}
