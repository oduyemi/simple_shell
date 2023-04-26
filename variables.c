#include "shell.h"

/**
 * is_chn - this will check if the current char in buffer is a chain delimeter
 * @info: parameter struct
 * @bf: the char buffer
 * @position: address of current position in bf
 *
 * Return: 1 if chain delimeter, else, 0
 */
int is_chn(info_b *info, char *bf, size_t *position)
{
	size_t i = *position;

	if (buf[i] == '|' && bf[i + 1] == '|')
	{
		bf[i] = 0;
		i++;
		info->cmd_bf_type = CMD_OR;
	}
	else if (bf[i] == '&' && bf[i + 1] == '&')
	{
		bf[i] = 0;
		i++;
		info->cmd_bf_type = CMD_AND;
	}
	else if (bf[i] == ';')
	{
		bf[i] = 0; 
		info->cmd_bf_type = CMD_CHN;
	}
	else
		return (0);
	*position = i;
	return (1);
}

/**
 * chk_chn - this will check whether we should continue chaining based on last status
 * @info: parameter struct
 * @bf: char buffer
 * @position: this is the location of current position in buf
 * @j: the starting position in bf
 * @bf_length: the length of bf
 *
 * Return: Void
 */
void chk_chn(info_b *info, char *bf, size_t *position, size_t j, size_t bf_length)
{
	size_t i = *position;

	if (info->cmd_bf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[j] = 0;
			i = bf_length;
		}
	}
	if (info->cmd_bf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[j] = 0;
			i = bf_length;
		}
	}

	*position = i;
}

/**
 * replace_alias - this will replace the aliases in the tokenized string
 * @info: parameter struct
 *
 * Return: 1 if replaced, else 0
 */
int replace_alias(info_b *info)
{
	int j;
	list_b *nodes;
	char *position;

	for (j = 0; j < 10; j++)
	{
		nodes = node_startswith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		fri(info->argv[0]);
		p = _stchr(node->st, '=');
		if (!position)
			return (0);
		p = _stdp(position + 1);
		if (!position)
			return (0);
		info->argv[0] = position;
	}
	return (1);
}

/**
 * replace_var - this will replace the var in the tokenized string
 * @info: parameter struct
 *
 * Return: 1 if replaced, else 0
 */
int replace_var(info_b *info)
{
	int j = 0;
	list_b *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_stcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
				_strdup(cnvert_no(info->status, 10, 0)));
			continue;
		}
		if (!_stcmp(info->argv[j], "$$"))
		{
			replace_string(&(info->argv[j]),
				_stdp(cnvert_no(gtpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->envn, &info->argv[j][1], '=');
		if (node)
		{
			replace_string(&(info->argv[j]),
				_stdup(_stchr(node->st, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _stdp(""));

	}
	return (0);
}

/**
 * replace_string - this will replace a string
 * @older: the location of an older string
 * @newer: the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **older, char *newer)
{
	fri(*old);
	*older = newer;
	return (1);
}
