/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:37:32 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:04:31 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_link(t_link **link)
{
	t_link	*root;

	if (!*link)
		return ;
	while (*link != NULL)
	{
		root = (*link)->next;
		free((*link)->value);
		free(*link);
		*link = root;
	}
	free(*link);
}

void	free_execute(t_glbl *glbl)
{
	int	i;

	i = 0;
	while (glbl->env[i] != NULL)
		free(glbl->env[i++]);
	free(glbl->env);
	i = 0;
	while (glbl->export[i] != NULL)
		free(glbl->export[i++]);
	free(glbl->export);
	free(glbl->input);
}

void	ft_free_cmd(void)
{
	t_command	*temp_e;
	int			i;

	i = -1;
	while (++i < g_glbl.cmd_count)
	{
		temp_e = g_glbl.cmd->next;
		ft_free_radi(g_glbl.cmd->radi);
		ft_free_exec(g_glbl.cmd->execute);
		free(g_glbl.cmd);
		g_glbl.cmd = temp_e;
	}
}

void	ft_free(t_list *list)
{
	int	i;

	i = -1;
	while (++i < list->list_len)
		free(list[i].value);
	free(list);
	free(g_glbl.input);
}

void	ft_decomp_free(int id, t_list *list, t_link *link)
{
	if (id == 2)
		ft_free(list);
	else if (id == 3)
	{
		ft_free_link(&link);
		free(list);
		free(g_glbl.input);
	}
	else if (id == 4)
	{
		ft_free_cmd();
		ft_free_link(&link);
		free(list);
		free(g_glbl.input);
	}
}
