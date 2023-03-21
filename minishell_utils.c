#include "minishell.h"

int	ft_opr_which(char input)
{
	if (input == '|')
		return (1);
	//if (input == '<' || input == '>')
	//	return (2);
	return (0);
}

int	ft_strlen(char *input, int index)
{
	int	i;

	i = 0;
	while (input[index] && input[index] != ' ')
	{
		index++;
		i++;
	}
	return (i);
}

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

void		ft_str_base(t_list *list, char *input, int *index)
{
	int			i;
	static int	now;

	i = -1;
	list[now].value = malloc(sizeof(char) * (ft_strlen(input, *index) + 1));
	while (input[*index] && input[*index] != ' ')
	{
		list[now].value[++i] = input[*index];
		*index += 1;
	}
	list[now].value[++i] = '\0'; 
	now++;
}

void	ft_uname(char *input, t_list *list)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] != ' ' && input[i])
			ft_str_base(list, input, &i);
	}
}