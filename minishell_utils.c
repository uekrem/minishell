#include "minishell.h"

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
		if (ft_opr_which(list[i].value[0]))
			list[i].type = PIPE;
		else if (i - 1 == -1)
			list[i].type = COMMAND;
		else if (ft_opr_which(list[i - 1].value[0]) == 1 
			&& ft_opr_which(list[i].value[0]) != 1)
		{
			list[i].type = COMMAND;
			list[i - 1].type = PIPE;
		}
		else if (ft_opr_which(list[i - 1].value[0]) > 1)
		{
			list[i].type = FILE_NAME;
			list[i - 1].type = OUTPUT_R;
			if (list[i - 1].value[0] == '<')
				list[i - 1].type = INPUT_R;
			if (list[i - 1].value[1] == '<')
				list[i - 1].type = D_INPUT_R;
			else if (list[i - 1].value[1] == '>')
				list[i - 1].type = D_OUTPUT_R;
		}
		else if ((list[i - 1].type == FILE_NAME && list[i - 3].type != COMMAND) 
					|| i - 3 == -1)
			list[i].type = COMMAND;
		else
			list[i].type = ARG;
	}
}