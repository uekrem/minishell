/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:29:21 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:38:56 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_outputs(t_command *cmd)
{
	t_radira	*redir;
	int			num;

	num = -1;
	redir = cmd->radi;
	while (redir)
	{
		if (redir->type == OUT_FILE)
			num = output(redir->value, OUT_FILE);
		else if (redir->type == IN_FILE)
			num = input(redir->value);
		else if (redir->type == D_INPUT_R)
			num = output(redir->value, D_INPUT_R);
		else if (redir->type == D_OUTPUT_R)
			dup2(cmd->heredoc_fd[0], 0);
		if (num == 0)
			return (0);
		redir = redir->next;
	}
	return (1);
}
