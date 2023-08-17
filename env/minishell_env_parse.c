/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:42 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:40:50 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_restrlen2(char *str, int *j)
{
	char	*search;
	char	*new_char;
	int		total;
	int		step;
	int		temp;

	total = 0;
	step = 0;
	temp = *j;
	*j += 1;
	search = NULL;
	search = ft_itoa(g_glbl.erorno);
	total += temp;
	total += ft_strlen(search, 0, '\0');
	total += ft_strlen(str, *j, '\0');
	new_char = malloc(sizeof(char) * (total + 1));
	ft_strwrite2(new_char, str, &step, temp - 1);
	ft_strwrite(new_char, search, &step, '\0');
	ft_strwrite(new_char, &str[*j], &step, '\0');
	new_char[step] = '\0';
	free(search);
	free(str);
	return (new_char);
}

char	*ft_restrlen(char *str, int *j)
{
	char	*search;
	char	*new_char;
	int		total;
	int		step;
	int		temp;

	total = 0;
	step = 0;
	temp = *j;
	search = NULL;
	search = ft_how_far(str, j);
	search = ft_env_search(search);
	if (search == NULL)
		return (ft_env_null_orien(search, str, j, temp));
	total += temp;
	total += ft_strlen(search, 0, '\0');
	total += ft_strlen(str, *j, '\0');
	new_char = malloc(sizeof(char) * (total + 1));
	ft_strwrite2(new_char, str, &step, temp - 1);
	ft_strwrite(new_char, search, &step, '\0');
	ft_strwrite(new_char, &str[*j], &step, '\0');
	new_char[step] = '\0';
	free(search);
	free(str);
	return (new_char);
}

void	ft_str_rebuild(t_list *list, int i)
{
	int	j;

	j = -1;
	if (list[i].value[j + 1] == '$')
		if (!list[i].value[j + 2])
			return ;
	while (list[i].value[++j])
	{
		if (list[i].value[j] == '$' && ft_quartes_selec(list[i].value, j) != 39)
		{
			j++;
			if (ft_stay_stop(list[i].value[j]))
			{
				if (list[i].value[j] == '?')
					list[i].value = ft_str_rebuild_query(list[i].value, &j);
				continue ;
			}
			list[i].value = ft_str_rebuild_base(list[i].value, &j);
		}
	}
}

void	ft_env_check(char *input, t_list *list)
{
	int	i;

	i = -1;
	while (++i < ft_str_shred(input))
	{
		if (list[i].type == D_OUTPUT_R)
		{
			i++;
			continue ;
		}
		ft_str_rebuild(list, i);
	}
}
