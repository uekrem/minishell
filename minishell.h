#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <unistd.h>

enum						e_token
{
	PIPE,
	OUTPUT_R,
	INPUT_R,
	D_OUTPUT_R,
	D_INPUT_R,
	ARG,
	COMMAND,
	FILE_NAME,
	FLAG,
	OUT_FILE,
	IN_FILE,
	END
};

typedef struct s_glbl
{
	char					**env;
	char					**export;
	char					*input;

}							t_glbl;

extern t_glbl				g_glbl;

typedef struct s_list
{
	enum e_token			type;
	int						list_len;
	int						flag;
	char					*value;
}							t_list;

typedef	struct s_link
{
	enum e_token			type;
	int						list_len;
	int						flag;
	char					*value;
	struct s_link			*prev;
	struct s_link			*next;
}	t_link;


typedef struct s_radira
{
	char					*value;
	enum e_token			type;
	struct s_radira			*prev;
	struct s_radira			*next;
}	t_radira;

typedef	struct s_execute
{
	char				*value;
	struct s_execute	*prev;
	struct s_execute	*next;
}	t_execute;

typedef struct s_command
{
	t_execute			*execute;
	t_radira			*radi;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

int							ft_opr_pair(char *input);
int							ft_str_shred(char *input);
int							ft_strlen(char *input, int index, char c);
int							ft_opr_which(char input);
void						ft_uname(t_list *list, char *input);
void						ft_untype(t_list *list);
void						ft_couple_core(char *input, int *i, char c);
void						ft_env_check(char *input, t_list *list);
char						*ft_restrlen(char *str, int *j);
char						*ft_appro_proc(char *str, int value);
void						ft_appro_name(t_list *list);
void						ft_str_base(t_list *list, char *input, int start,
							int finish, int *now);

char						*ft_piece(char *env);
void						ft_builtins(t_list *list);
void						ft_echo(t_list *list, int *i);
void						ft_pwd(t_list *list, int *i);
void						ft_cd(t_list *list, int *i);
void						ft_export(t_list *list);
int							arg_count(t_list *list);
int							export_size(void);
void						ft_env(t_list *list);
void						init_env(t_list *list);
void						ft_unset(t_list *list, int *i);
void						ctrl_d(t_glbl *glbl);
void						free_execute(t_glbl *glbl);
void						free_char(char **arg);

void						ft_strwrite2(char *new_str, char *str, int *step, int c);
void						ft_free(t_list *list);
t_link						*ft_lstnew(t_list *list);
void						ft_lstadd_back(t_link **lst, t_link *new);
t_link						*ft_lstlast(t_link *lst);
int	 						ft_parse_eror(t_link *link);
void						ft_fill_command(t_command **cmd, t_link *link);

// void						fill_command(t_list *list, t_command *cmd);
// int							count_arguman(t_list *list);

#endif
