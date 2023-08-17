/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:49:49 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 13:49:50 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_opr_step(char *input, int *i)
{
	*i += 1;
	if (ft_opr_which(input[*i]) > 1 && input[*i] != input[(*i) - 1])
		return ;
	else if (ft_opr_which(input[*i]) > 1)
		*i += 1;
}

int	ft_while_break(char *input, int *i, char *c)
{
	*i += 1;
	if (input[*i] == *c && *c != ' ')
		*c = ' ';
	else if ((input[*i] == '"' || input[*i] == 39) && *c == ' ')
	{
		*c = input[(*i)++];
		if (input[*i] == *c)
			*c = ' ';
	}
	else if (ft_opr_which(input[*i]) && *c == ' ')
		return (1);
	return (0);
}

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

int	ft_strlen(char *input, int index, char c)
{
	int	i;

	i = 0;
	while (input[index] && input[index] != c)
	{
		i++;
		index++;
	}
	return (i);
}
