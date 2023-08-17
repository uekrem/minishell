/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:08 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:38:06 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_arguman(t_command *cmd, t_link **link)
{
	if ((*link)->type == ARG)
	{
		cmd->execute = fill_execute(*link, &cmd->execute);
	}
	else if ((*link)->type == D_INPUT_R)
	{
		cmd->radi = fill_redirect(*link, &cmd->radi);
	}
	else if ((*link)->type == D_OUTPUT_R)
	{
		cmd->radi = fill_redirect(*link, &cmd->radi);
	}
	else if ((*link)->type == INPUT_R || (*link)->type == OUTPUT_R)
	{
		cmd->radi = fill_redirect(*link, &cmd->radi);
	}
}

void	add_back_cmd(t_command *new_cmd)
{
	t_command	*tmp;

	tmp = g_glbl.cmd;
	if (!(tmp))
		g_glbl.cmd = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

t_command	*setup_cmd(void)
{
	t_command	*new_cmd;

	new_cmd = ft_calloc(sizeof(t_command), 1);
	pipe(new_cmd->fd);
	new_cmd->pid = -1;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	ft_fill_command(t_link *link)
{
	t_command	*new_cmd;

	(void)new_cmd;
	g_glbl.cmd = NULL;
	new_cmd = NULL;
	while (link)
	{
		if (link->type == PIPE || link->prev == NULL)
		{
			if (link->type == PIPE)
				link = link->next;
			new_cmd = setup_cmd();
			add_back_cmd(new_cmd);
			g_glbl.cmd_count++;
		}
		if (!link)
			break ;
		add_arguman(new_cmd, &link);
		if (link)
			link = link->next;
	}
	return (0);
}
