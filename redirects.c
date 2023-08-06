#include "minishell.h"

void	redirect_inputs(t_command *cmd)
{
	t_radira	*redir;

	redir = cmd->radi;
	while (redir)
	{
		if (redir->type == IN_FILE)
			input(redir->value);
		else if (redir->type == D_OUTPUT_R)
			dup2(cmd->heredoc_fd[0], 0);
		redir = redir->next;
	}
}

void	redirect_outputs(t_command *cmd)
{
	t_radira	*redir;

	redir = cmd->radi;
	while (redir)
	{
		if (redir->type == OUT_FILE)
			output(redir->value, OUT_FILE);
		else if (redir->type == D_INPUT_R)
			output(redir->value, D_INPUT_R);
		redir = redir->next;
	}
}
