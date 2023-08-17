/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_creat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:39 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:40:48 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_how_far(char *str, int *j)
{
	int		counter;
	int		value;
	char	*search;

	value = 0;
	counter = 0;
	while (str[*j])
	{
		if (ft_how_far_chec(str[*j]))
			break ;
		value++;
		*j += 1;
	}
	search = malloc(sizeof(char) * (value + 1));
	while (value > 0)
	{
		search[counter] = str[*j - value];
		counter++;
		value--;
	}
	search[counter] = '\0';
	return (search);
}

char	*ft_env_search(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (g_glbl.env[++i])
	{
		j = -1;
		while (g_glbl.env[i][++j])
		{
			if (str[j] == g_glbl.env[i][j])
				continue ;
			break ;
		}
		if (g_glbl.env[i][j] == '=' && str[j] == '\0')
			break ;
	}
	free(str);
	if (g_glbl.env[i])
		return (ft_piece(g_glbl.env[i]));
	return (NULL);
}

char	*ft_env_null(char *str, int *j, int temp)
{
	char	*new_char;
	int		total;
	int		step;

	total = 0;
	step = 0;
	total += temp;
	total += ft_strlen(str, *j, '\0');
	new_char = malloc(sizeof(char) * (total + 1));
	ft_strwrite2(new_char, str, &step, temp - 1);
	ft_strwrite(new_char, &str[*j], &step, '\0');
	new_char[step] = '\0';
	free(str);
	return (new_char);
}

char	*ft_str_rebuild_query(char *list, int *j)
{
	int	temp;

	temp = ft_strlen(list, 0, '\0');
	list = ft_restrlen2(list, j);
	(*j) = ((*j) - (temp - ft_strlen(list, 0, '\0'))) - 1;
	return (list);
}

char	*ft_str_rebuild_base(char *list, int *j)
{
	int	temp;

	temp = ft_strlen(list, 0, '\0');
	list = ft_restrlen(list, j);
	(*j) = ((*j) - (temp - ft_strlen(list, 0, '\0'))) - 1;
	return (list);
}
