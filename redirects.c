#include "minishell.h"

// int	redirect_inputs(t_command *cmd)
// {
// 	t_radira	*redir;
// 	int			num;

// 	num = -1;
// 	redir = cmd->radi;
// 	while (redir)
// 	{
		
		
// 		if (num == 0)
// 			return (num);
// 		redir = redir->next;
// 	}
// 	return (1);
// }

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
