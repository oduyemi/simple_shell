#include "shell.h"

/**
 * hsh_ - this is the main shell loop
 * @info: this is the parameter & return info struct
 * @ar: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh_(info_b *info, char **ar)
{
	ssize_t r = 0;
	int builtin_rt = 0;

	while (r != -1 && builtin_rt != -2)
	{
		clear_info(info);
		if (inte(info))
			_puts("$ ");
		_eputchar(BF_FLUSH);
		r = gt_input(info);
		if (r != -1)
		{
			st_info(info, ar);
			builtin_rt = fnd_builtin(info);
			if (builtin_rt == -1)
				fnd_cmd(info);
		}
		else if (inte(info))
			_putchar('\n');
		fri_info(info, 0);
	}
	wrte_history(info);
	fri_info(info, 1);
	if (!inte(info) && info->status)
		exit(info->status);
	if (builtin_rt == -2)
	{
		if (info->err_no == -1)
			exit(info->status);
		exit(info->err_no);
	}
	return (builtin_rt);
}

/**
 * fnd_builtin - this will find a builtin command
 * @info: this is a parameter and it returns info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin is successfully executed,
 *			1 if builtin is seen but not successful,
 *			-2 if builtin signals exit()
 */
int fnd_builtin(info_t *info)
{
	int i, built_in_rt = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"envn", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"stenvn", _mysetenv},
		{"unstenvn", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[s].type; s++)
		if (_stcmp(info->argv[0], builtintbl[s].type) == 0)
		{
			info->ln_count++;
			built_in_rt = builtintbl[i].func(info);
			break;
		}
	return (built_in_rt);
}

/**
 * fnd_cmd - this will find a command in PATH
 * @info: a parameter and it will return info struct
 *
 * Return: void
 */
void fnd_cmd(info_b *info)
{
	char *path = NULL;
	int s, b;

	info->path = info->argv[0];
	if (info->lncount_flag == 1)
	{
		info->ln_count++;
		info->lncount_flag = 0;
	}
	for (s = 0, b = 0; info->arg[s]; s++)
		if (!is_delm(info->arg[s], " \t\n"))
			b++;
	if (!b)
		return;

	path = fnd_path(info, _gtenvn(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		frk_cmd(info);
	}
	else
	{
		if ((inte(info) || _gtenvn(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			frk_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			prnt_error(info, "not found\n");
		}
	}
}

/**
 * frk_cmd - this will fork an exec thread to run cmd
 * @info: a parameter and will return info struct
 *
 * Return: void
 */
void frk_cmd(info_b *info)
{
	pid_b child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (exe_cve(info->path, info->argv, get_environ(info)) == -1)
		{
			fri_info(info, 1);
			if (err_no == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prnt_error(info, "Permission denied\n");
		}
	}
}
