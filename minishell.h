#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
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
	END
};

typedef struct s_list
{
	enum e_token	type;
	char			*value;
	char			quates;
	char			**env;
}			t_list;

int		ft_opr_pair(char *input);
int		ft_str_shred(char *input);
int		ft_strlen(char *input, int index, char c);
int		ft_opr_which(char input);
void	ft_uname(char *input, t_list *list);
void	ft_untype(char *input, t_list *list);
void	ft_env_check(char *input, t_list	*list);
char	*ft_restrlen(t_list *list, char *str, int *j);

#endif
