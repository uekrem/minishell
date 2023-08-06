#include "minishell.h"

int	contain_heredoc()
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
	if (cmd->prev == NULL){
		dup2(cmd->fd[1], 1);
		if(cmd->fd[1] != 1)
			close(cmd->fd[1]);
	}
	else if(cmd->next == NULL){
		dup2(cmd->prev->fd[0], 0);
		if(cmd->prev->fd[0] != 0)
			close(cmd->fd[0]);
	}
	else
	{
		dup2(cmd->prev->fd[0], 0);
		if(cmd->prev->fd[0] != 0)
			close(cmd->prev->fd[0]);
		dup2(cmd->fd[1], 1);
		if(cmd->fd[1] != 1)
			close(cmd->fd[1]);
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
		else
			pipe_route(cmd);
	}
	redirect_inputs(cmd);
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
		ft_builtins();
		path = get_path(cmd->execute->value);
		args = get_arg_fill(cmd->execute);
		//printf("%s\n\n", path);
		//getchar();
		execve(path, args, g_glbl.env);
		command_err(cmd->execute->value);
		exit(errno);
	}
	else
		cmd->pid = pid;
}
