/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:26:24 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:03:32 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc_fd(t_command *cmd)
{
	if (contain_heredoc() && cmd->heredoc_fd[0] > 2)
		close(cmd->heredoc_fd[0]);
}

void	close_all_fd(void)
{
	t_command	*cmd;

	cmd = g_glbl.cmd;
	while (cmd)
	{
		close_heredoc_fd(cmd);
		if (cmd->fd[0] > 2)
			close(cmd->fd[0]);
		if (cmd->fd[1] > 2)
			close(cmd->fd[1]);
		cmd = cmd->next;
	}
}
