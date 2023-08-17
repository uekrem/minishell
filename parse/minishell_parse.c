/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:33 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:34:19 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_str_base(t_list *list, int start, int finish, int now)
{
	int	i;

	i = 0;
	list[now].value = malloc(sizeof(char) * ((finish - start) + 1));
	while (g_glbl.input[start] && start != finish)
	{
		list[now].value[i] = g_glbl.input[start];
		start += 1;
		i++;
	}
	list[now].value[i] = '\0';
	list[now].type = 99;
}

void	ft_uname(t_list *list, char *input)
{
	int	i;
	int	now;
	int	temp;

	i = 0;
	now = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		temp = i;
		if (input[i])
		{
			ft_couple_core(input, &i, input[i]);
			ft_str_base(list, temp, i, now);
			now++;
		}
	}
	list[now].value = NULL;
}

void	ft_untype(t_list *list)
{
	int	i;

	i = -1;
	while (++i < list->list_len)
	{
		if (list[i].type != 99)
			continue ;
		list[i].type = ARG;
		if (list[i].value[0] == '<' && list[i].value[1] == '<')
			list[i].type = D_OUTPUT_R;
		else if (list[i].value[0] == '>' && list[i].value[1] == '>')
			list[i].type = D_INPUT_R;
		else if (list[i].value[0] == '>')
			list[i].type = INPUT_R;
		else if (list[i].value[0] == '<')
			list[i].type = OUTPUT_R;
		else if (list[i].value[0] == '|')
			list[i].type = PIPE;
	}
	list[i].type = END;
}

char	*ft_appro_proc(char *str, int value)
{
	int		i;
	int		flag;
	int		indepent;
	char	*new_str;

	i = -1;
	flag = 0;
	indepent = -1;
	new_str = malloc(sizeof(char) * (value + 1));
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == 39) && flag == 0)
			flag = str[i];
		else if (flag != 0 && str[i] == flag)
			flag = 0;
		else
			new_str[++indepent] = str[i];
	}
	new_str[++indepent] = '\0';
	free(str);
	return (new_str);
}

void	ft_appro_name(t_list *list)
{
	int	i;
	int	j;
	int	flag;
	int	value;

	i = -1;
	while (++i < list->list_len)
	{
		flag = 0;
		value = 0;
		j = -1;
		while (list[i].value[++j])
		{
			if ((list[i].value[j] == '"' || list[i].value[j] == 39)
				&& flag == 0)
				flag = list[i].value[j];
			else if (flag != 0 && list[i].value[j] == flag)
				flag = 0;
			else
				value++;
		}
		list[i].value = ft_appro_proc(list[i].value, value);
	}
}
