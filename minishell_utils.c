#include "minishell.h"

void		ft_str_rebuild(t_list *list, int i)
{
	int		j;

	j = -1;
	while (list[i].value[++j])
	{
		if (list[i].value[j] == '$')
		{
			j++;
			list[i].value = ft_restrlen(list, list[i].value, &j);
			j = -1;
		}
	}
}

void		ft_env_check(char *input, t_list *list)		//(quates değeri ' ' olduğu zamanda çalışmalı -> echo $USER)
{
	int	i;

	i = -1;
	while (++i < ft_str_shred(input))
	{
		if ((list[i].quates = ' ' || list[i].quates == '"') && list[i].type == ENV)
			ft_str_rebuild(list, i);
	}
}

void		ft_str_base(t_list *list, char *input, int *index, int *now)
{
	int			i;
	char		c;
	int			len;

	i = 0;
	c = ' ';
	if (input[*index] == '"' || input[*index] == 39)
		c = input[*index];
	if (c != ' ')
	{
		len = *index + 1;
		while (input[len] != c && input[len])
		{
			len += 1;
			if (input[len] == c)
				c = ' ';
		}
		c = input[*index];
		list[*now].value = malloc(sizeof(char) * ((len - *index) + 1));
		while (input[*index] && *index != len)
		{
			list[*now].value[i] = input[*index];
			*index += 1;
			i++;
		}
	}
	else
	{
		len = *index;
		while (input[len] != c && input[len])
		{
			if ((input[len] == '"' || input[len] == 39)
				&& c == ' ')
				c = input[len];
			len++;
		}
		while (input[len] != ' ' && input[len])
			len++;
		list[*now].value = malloc(sizeof(char) * ((len - *index) + 2));
		while (input[*index] && *index != len)
		{
			list[*now].value[i] = input[*index];
			*index += 1;
			i++;
		}
		c = ' ';
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
				if (list[i].value[j] == '$' && list[i].quates != 39)
					list[i].type = ENV;
		}
	}
}