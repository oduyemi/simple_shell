#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READ_BF_SIZE 1024
#define WRITE_BF_SIZE 1024
#define BF_FLUSH -1

/* command chain */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GTLINE 0
#define USE_STTOK 0

#define HISTORY_FILE	".simple_shell_past"
#define HISTORY_MAX	4096

extern char **envn;


/**
 * struct liststr - singly linked list
 * @no: the number field
 * @st: a string
 * @nx_node: points to the next node
 */
typedef struct list_st
{
	int no;
	char *st;
	struct list_st *nx_node;
} list_b;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@ln_count: the error count
 *@err_no: error code
 *@lncount_flg: if on count this line of input
 *@filename: the program filename
 *@ev: linked list local copy of environ
 *@envn: custom modified copy of environ from LL env
 *@history_node: the history node
 *@alias_node: the alias node
 *@ev_chnge: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_bf: address of pointer to cmd_bf, on if chaining
 *@cmd_bf_type: CMD_type ||, &&, ;
 *@read_xy: the xy from which to read line input
 *@history_count: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int ln_count;
	int err_no;
	int lncount_flg;
	char *filename;
	list_b *ev;
	list_b *history_node;
	list_b *alias_node;
	char **envn;
	int ev_chnge;
	int status;

	char **cmd_bf; /* pointer to cmd ; chain buffer, for memory */
	int cmd_bf_type; /* CMD_type ||, &&, ; */
	int read_xy;
	int history_count;
} info_b;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_b *);
} builtin_table;


/* toem_shloop.c */
int hsh_(info_b *, char **);
int fnd_builtin(info_b *);
void fnd_cmd(info_b *);
void frk_cmd(info_b *);

/* toem_parser.c */
int is_cmd(info_b *, char *);
char *dp_chars(char *, int, int);
char *fnd_path(info_b *, char *, char *);

/* loophsh.c */
int loophsh_(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _stlen(char *);
int _stcmp(char *, char *);
char *startswith(const char *, const char *);
char *_stcat(char *, char *);

/* toem_string1.c */
char *_stcpy(char *, char *);
char *_stdp(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_stncpy(char *, char *, int);
char *_stncat(char *, char *, int);
char *_stchr(char *, char);

/* toem_tokenizer.c */
char **sttow(char *, char *);
char **sttow2(char *, char);

/* toem_realloc.c */
char *_memst(char *, char, unsigned int);
void ffri(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfri(void **);

/* toem_atoi.c */
int inte(info_b *);
int is_delm(char, char *);
int _isalphabeth(int);
int _atoi(char *);

/* toem_errors1.c */
int _err_atoi_(char *);
void prnt_error(info_b *, char *);
int prnted(int, int);
char *cnvert_no(long int, int, int);
void remove_cment(char *);

/* toem_builtin.c */
int _myexit(info_b *);
int _mycd(info_b *);
int _myhelp(info_b *);

/* toem_builtin1.c */
int _myhistory(info_b *);
int _myalias(info_b *);

/*toem_getline.c */
ssize_t gt_input(info_b *);
int _gtline(info_b *, char **, size_t *);
void logintHandler(int);

/* toem_getinfo.c */
void cl_info(info_b *);
void st_info(info_b *, char **);
void fri_info(info_b *, int);

/* toem_environ.c */
char *_gtenvn(info_b *, const char *);
int _myenvn(info_b *);
int _mysetevn(info_b *);
int _myunestenvn(info_b *);
int populate_envn_list(info_b *);

/* toem_getenv.c */
char **gt_envn(info_b *);
int _unsetenvn(info_b*, char *);
int _setenvn(info_b *, char *, char *);

/* toem_history.c */
char *gt_history_file(info_b *info);
int wrte_history(info_b *info);
int rd_history(info_b *info);
int build_history_list(info_b *info, char *bf, int lncount);
int reno_history(info_b *info);

/* toem_lists.c */
list_t *add_node(list_b **, const char *, int);
list_t *add_nodeend(list_b **, const char *, int);
size_t prnt_list_st(const list_b *);
int delete_node_at_index(list_b **, unsigned int);
void fri_list(list_b **);

/* toem_lists1.c */
size_t list_len(const list_b *);
char **list_to_sts(list_b *);
size_t prnt_list(const list_b *);
list_t *node_startswith(list_b *, char *, char);
ssize_t gt_node_index(list_b *, list_b *);

/* toem_vars.c */
int is_chn(info_b *, char *, size_t *);
void chk_chn(info_b *, char *, size_t *, size_t, size_t);
int replace_alias(info_b *);
int replace_var(info_b *);
int replace_st(char **, char *);

#endif
