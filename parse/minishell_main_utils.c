/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:39:13 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:18:56 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_envair(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_glbl.env = malloc(sizeof(char *) * (i + 1));
	g_glbl.export = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		g_glbl.env[i] = ft_strdup(env[i]);
		g_glbl.export[i] = ft_strdup(env[i]);
		i++;
	}
	g_glbl.env[i] = NULL;
	g_glbl.export[i] = NULL;
}

int	ft_pipe_more(t_list *list)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	if (list[0].type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		g_glbl.erorno = 258;
		return (1);
	}
	while (list[++i].value)
	{
		if (list[i].type == PIPE && flag == 0)
			flag = 1;
		else if (list[i].type == PIPE && flag == 1)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			g_glbl.erorno = 258;
			return (1);
		}
		else if (list[i].type != PIPE && flag == 1)
			flag = 0;
	}
	return (0);
}
