#include "minishell.h"

void		ft_str_rebuild(t_list *list, int i)
{
	char	*new_char;
	int		j;

	j = -1;
	while (list[i].value[++j])
	{
		if (list[i].value[j] == '$')
		{
			j++;
			new_char = ft_restrlen(list, list[i].value, &j);
		}
	}
	printf("%s\n", new_char);
}

void		ft_env_check(char *input, t_list *list)		//$ girince değerini diziye ekleme (" ve ' arasındaki farka göre / drive'a bak) (quates değeri ' ' olduğu zamanda çalışmalı -> echo $USER)
{
	int	i;

	i = -1;
	while (++i < ft_str_shred(input))
	{
		if (list[i].quates == '"' && list[i].type == ENV)
			ft_str_rebuild(list, i);
	}
}

void		ft_str_base(t_list *list, char *input, int *index, int *now)
{
	int			i;
	char		c;

	i = 0;
	c = ' ';
	if (input[*index] == '"' || input[*index] == 39)
	{
		c = input[*index];
		*index += 1;
	}
	list[*now].value = malloc(sizeof(char) * (ft_strlen(input, *index, c) + 1));
	while (input[*index] && input[*index] != c)
	{
		list[*now].value[i] = input[*index];
		*index += 1;
		i++;
	}
	list[*now].value[i] = '\0';
	list[*now].quates = c;
	*now += 1;
}

void	ft_uname(char *input, t_list *list)
{
	int	i;
	int	now;

	i = -1;
	now = 0;
	while (input[++i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] != ' ' && input[i])
			ft_str_base(list, input, &i, &now);
	}
}

void	ft_untype(char *input, t_list *list)
{
	int	i;
	int	j;

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
		{
			list[i].type = ARG;
			j = -1;
			while (list[i].value[++j])
				if (list[i].value[j] == '$' && list[i].quates == '"')
					list[i].type = ENV;
		}
	}
}