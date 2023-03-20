#include "minishell.h"

int	ft_str_shred(char *input)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;

	while (input[i])
	{
		while ((input[i] == ' ' || input[i] == '"') && input[i])
			i++;
		if (input[i])
			flag++;
		while (input[i] != ' ' && input[i] != '"' && input[i])
			i++;
	}
	return (flag);
}

int		ft_uname(char *input, t_list *list)
{
	
}