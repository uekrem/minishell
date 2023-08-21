/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:36 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:39:22 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contain_heredoc(void)
{
	t_radira	*radir;

	radir = g_glbl.cmd->radi;
	while (radir)
	{
		if (radir->type == D_OUTPUT_R)
			return (1);
		if (radir->next)
			radir = radir->next;
		else
			break ;
	}
	return (0);
}

void	pipe_route(t_command *cmd)
{
	if (cmd->prev == NULL)
		dup2(cmd->fd[1], 1);
	else if (cmd->next == NULL)
		dup2(cmd->prev->fd[0], 0);
	else
	{
		dup2(cmd->prev->fd[0], 0);
		dup2(cmd->fd[1], 1);
	}
}

void	heredoc_route(t_command *cmd)
{
	dup2(cmd->heredoc_fd[0], 0);
	if (cmd->next != NULL)
		dup2(cmd->fd[1], 1);
}

void	cmd_route(t_command *cmd)
{
	if (g_glbl.cmd_count > 1)
	{
		if (contain_heredoc())
			heredoc_route(cmd);
		pipe_route(cmd);
	}
	redirect_outputs(cmd);
	close_all_fd();
}

void	actuation(t_command *cmd)
{
	pid_t	pid;
	char	*path;
	char	**args;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		g_glbl.parent_pid = 0;
		cmd_route(cmd);
		if (ft_builtins(cmd))
			exit(g_glbl.erorno);
		if (cmd->execute != NULL)
		{
			path = get_path(cmd->execute->value);
			args = get_arg_fill(cmd->execute);
		}
		execve(path, args, g_glbl.env);
		if (cmd->execute != NULL)
			command_err(cmd->execute->value);
		exit(errno);
	}
	else
		cmd->pid = pid;
}
