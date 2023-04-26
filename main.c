#include "shell.h"

/**
 * main - entry point
 * @ag: arg count
 * @ar: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ag, char **ar)
{
	info_b info[] = { INFO_INIT };
	int xy = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (xy)
		: "r" (xy));

	if (ag == 2)
	{
		xy = open(ar[1], O_RDONLY);
		if (xy == -1)
		{
			if (err_no == EACCES)
				exit(126);
			if (err_no == ENOENT)
			{
				_eputs(ar[0]);
				_eputs(": 0: Can't open ");
				_eputs(ar[1]);
				_eputchar('\n');
				_eputchar(BF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_xy = xy;
	}
	populate_envn_list(info);
	rd_history(info);
	hsh_(info, ar);
	return (EXIT_SUCCESS);
}
