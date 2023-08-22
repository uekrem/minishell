/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_sum.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:30 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/22 11:57:51 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pair_sum(int *arg, int *flag)
{
	if ((*arg) == 0)
		(*arg) = 1;
	else
		(*arg) = 0;
	(*flag)++;
}

void	ft_pair_sum2(int *arg2, int *flag2)
{
	if ((*arg2) == 0)
		(*arg2) = 1;
	else
		(*arg2) = 0;
	(*flag2)++;
}

int	ft_opr_pair(char *input)
{
	int	i;
	int	arg;
	int	arg2;
	int	flag;
	int	flag2;

	i = -1;
	arg = 1;
	arg2 = 1;
	flag = 0;
	flag2 = 0;
	while (input[++i])
	{
		if (input[i] == '"' && arg2 == 1)
			ft_pair_sum(&arg, &flag);
		else if (input[i] == 39 && arg == 1)
			ft_pair_sum2(&arg2, &flag2);
	}
	if (flag % 2 == 0 && flag2 % 2 == 0)
		return (0);
	printf("Missing double or single quotes\n");
	g_glbl.erorno = 258;
	free(g_glbl.input);
	return (1);
}

void	ft_couple_core(char *input, int *i, char c)
{
	c = ' ';
	if (input[*i] == '|')
	{
		*i += 1;
		return ;
	}
	else if (ft_opr_which(input[*i]))
	{
		ft_opr_step(input, i);
		return ;
	}
	if (input[*i] == 39 || input[*i] == '"')
	{
		c = input[*i];
		*i += 1;
		if (input[*i] == c)
			c = ' ';
	}
	while (input[*i] && input[*i] != c)
	{
		if (ft_while_break(input, i, &c))
			break ;
	}
}

int	ft_str_shred(char *input)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (input[i])
			flag++;
		if (input[i])
			ft_couple_core(input, &i, input[i]);
	}
	return (flag);
}
