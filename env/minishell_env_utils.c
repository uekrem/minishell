/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:45 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:40:52 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strwrite(char *new_str, char *str, int *step, char c)
{
	int	j;

	j = 0;
	while (str[j] != c && str[j])
	{
		new_str[*step] = str[j];
		*step += 1;
		j++;
	}
}

void	ft_strwrite2(char *new_str, char *str, int *step, int c)
{
	int	j;

	j = 0;
	while (j < c && str[j])
	{
		new_str[*step] = str[j];
		*step += 1;
		j++;
	}
}

int	ft_stay_stop(char c)
{
	if (((c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96)
			|| (c >= 123 && c <= 126) || c == ' ') && c)
		return (1);
	return (0);
}

char	ft_quartes_selec(char *str, int i)
{
	int		num;
	char	c;
	int		check;

	num = -1;
	check = 1;
	while (++num < i)
	{
		if ((str[num] == 39 || str[num] == '"') && check)
		{
			check = 0;
			c = str[num];
		}
		else if (str[num] == c && !check)
		{
			check = 1;
			c = ' ';
		}
	}
	return (c);
}

char	*ft_piece(char *env)
{
	char	*piece;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (env[i] != '=')
		++i;
	++i;
	piece = malloc(sizeof(char) * (ft_strlen(env, i, '\0') + 1));
	while (env[i])
	{
		piece[++j] = env[i];
		i++;
	}
	piece[++j] = '\0';
	return (piece);
}
