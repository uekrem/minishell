#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

enum		e_token
{
	PIPE,
	OUTPUT_R,
	INPUT_R,
	D_OUTPUT_R,
	D_INPUT_R,
	ARG,
	COMMAND,
	FILE_NAME,
	ENV,
	FLAG,
	END
};

typedef struct s_glbl
{
	char			**env;
	char			**export;
}			t_glbl;

extern t_glbl g_glbl;

typedef struct s_list
{
	enum e_token	type;
	int				list_len;
	int				flag;
	char			*value;
	char			quates;
}			t_list;

int		ft_opr_pair(char *input);
int		ft_str_shred(char *input);
int		ft_strlen(char *input, int index, char c);
int		ft_opr_which(char input);
void	ft_uname(char *input, t_list *list);
void	ft_untype(char *input, t_list *list);
void	ft_env_check(char *input, t_list	*list);
char	*ft_restrlen(char *str, int *j);
char	*ft_appro_proc(char *str, int value);
void	ft_appro_name(t_list *list);

char	*ft_piece(char *env);
void	ft_builtins(char *input, t_list *list);
void	ft_echo(char *input, t_list *list, int *i);
void	ft_pwd(t_list *list, int *i);
void	ft_cd(t_list *list, int *i);
void	ft_export(t_list *list);
int		arg_count(t_list *list);
void	ft_env();
void	init_env(t_list *list);
void	ft_unset(t_list *list);

#endif
