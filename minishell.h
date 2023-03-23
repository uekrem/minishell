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
	END
};

typedef struct s_list
{
	enum e_token	type;
	char			*value;
}			t_list;

int		ft_str_shred(char *input);
void	ft_uname(char *input, t_list *list);
void	ft_untype(char *input, t_list *list);

#endif
