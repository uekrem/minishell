/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:45:34 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 13:45:35 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_flag(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[0] != '-')
			break ;
		else if (i != 0 && str[i] == '-')
			break ;
	}
	if (!str[i])
		return (1);
	return (0);
}

char	ft_issue(char *str, char sea)
{
	int		i;
	char	c;

	i = -1;
	c = ' ';
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == 39) && c == ' ')
			c = str[i];
		else if (str[i] == c)
			c = ' ';
		else if (str[i] == sea)
			return (c);
	}
	return (0);
}
