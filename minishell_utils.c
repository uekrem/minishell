#include "minishell.h"

int	ft_opr_which(char input)
{
	if (input == '|')
		return (1);
	if (input == '<')
		return (2);
	if (input == '>')
		return (3);
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

void		ft_str_base(t_list *list, char *input, int *index, int now)
{
	int			i;

	i = 0;
	list[now].value = malloc(sizeof(char) * (ft_strlen(input, *index) + 1));
	while (input[*index] && input[*index] != ' ')
	{
		list[now].value[i] = input[*index];
		*index += 1;
		i++;
	}
	list[now].value[i] = '\0';
	list[now].type = 3;
	now++;
}

void	ft_uname(char *input, t_list *list)
{
	int	i;
	int	now;

	now = 0;
	i = -1;
	while (input[++i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] != ' ' && input[i])
		{
			ft_str_base(list, input, &i, now);
			now++;
		}
	}
}

void	ft_untype(char *input, t_list *list)
{
	int	i;

	i = -1;
	while (++i < ft_str_shred(input))
	{
		if (list[i].value[0] == '|')
			list[i].type = PIPE;
		if (i - 1 == -1)
			list[i].type = COMMAND;
		else if (list[i - 1].value[0] == '|' 
			&& list[i].value[0] != '|')
		{
			list[i].type = COMMAND;
			list[i - 1].type = PIPE;
		}
		else if (list[i - 1].value[0] == '>' || list[i - 1].value[0] == '<')
		{
			list[i].type = FILE_NAME;
			list[i - 1].type = OUTPUT_R;
			if (list[i - 1].value[0] == '<')
				list[i - 1].type = INPUT_R;
		}
		else if (i - 3 == -1 || (list[i - 1].type == FILE_NAME && list[i - 2].type != COMMAND 
			&& list[i - 3].type != COMMAND))
			list[i].type = COMMAND;
		else
			list[i].type = ARG;
	}
}