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
		if (input[i] && !ft_opr_which(input[i]))
			flag++;
		while (input[i] != ' ' && input[i] != '"' && input[i])
			i++;
	}
	return (flag);
}

int		ft_str_base(t_list *list, char *input, int *index)
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
	return (now - 1);
}

void	ft_uname(char *input, t_list *list)
{
	int	i;
	int	flag;
	int	now;

	flag = 0;
	i = -1;
	while (input[++i])
	{
		while (input[i] == ' ')
			i++;
		if (ft_opr_which(input[i]))
		{
			flag = 1;
			i++;
		}
		if (input[i] != ' ' && input[i])
			now = ft_str_base(list, input, &i);
		/*if (flag == 1)
			list[now].type = 5;
		else
			list[now].type = 4;*/
		flag = 0;
	}
}