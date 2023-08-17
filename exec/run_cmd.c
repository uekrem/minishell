/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:29:31 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:40:33 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtins(t_command *cmd)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	if (redirect_outputs(cmd) == 0)
		return ;
	ft_builtins(cmd);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

void	wait_cmd(void)
{
	t_command	*cmd;

	cmd = g_glbl.cmd;
	close_all_fd();
	while (cmd != NULL)
	{
		if (cmd->pid != -1)
		{
			waitpid(cmd->pid, &errno, 0);
			if (WIFEXITED(errno))
				g_glbl.erorno = WEXITSTATUS(errno);
			else if (WIFSIGNALED(errno))
				g_glbl.erorno = 128 + WTERMSIG(errno);
		}
		cmd = cmd->next;
	}
}

void	fill_heredoc(void)
{
	t_command	*cmd;
	t_radira	*redir;

	cmd = g_glbl.cmd;
	while (cmd)
	{
		redir = cmd->radi;
		while (redir)
		{
			if (redir->type == D_OUTPUT_R)
				heredoc(cmd->heredoc_fd, redir->value);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	is_builtin(t_command *cmd)
{
	if (which_commant(cmd->execute->value, "echo"))
		return (1);
	else if (which_commant(cmd->execute->value, "cd"))
		return (1);
	else if (which_commant(cmd->execute->value, "pwd"))
		return (1);
	else if (which_commant(cmd->execute->value, "export"))
		return (1);
	else if (which_commant(cmd->execute->value, "unset"))
		return (1);
	else if (which_commant(cmd->execute->value, "env"))
		return (1);
	else if (which_commant(cmd->execute->value, "exit"))
		return (1);
	return (0);
}

void	run_cmd(void)
{
	t_command	*cmd;

	cmd = g_glbl.cmd;
	if (!cmd)
		return ;
	fill_heredoc();
	if (g_glbl.heredoc)
		return ;
	if (cmd->execute != 0 && g_glbl.cmd_count == 1 && is_builtin(cmd))
	{
		run_builtins(cmd);
		cmd = cmd->next;
	}
	while (cmd)
	{
		actuation(cmd);
		cmd = cmd->next;
	}
	wait_cmd();
}
