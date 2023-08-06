#include "minishell.h"

void	interreput(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(errno);
}

void	get_input(char *endline, int *fd)
{
	char *input;

	signal(SIGINT, interreput);
	while (1)
	{
		input = readline("heredoc>> ");
		if (!input || (which_commant(input, endline) && ft_strlenn(input) == ft_strlenn(endline)))
		{
			free(input);
			exit(1);
		}
		write(fd[1], input, ft_strlenn(input));
		write(fd[1], "\n", 1);
		free(input);
	}
}

void	heredoc(int *fd, char *endline)
{
	int	pid;
	int	status;

	if (pipe(fd) < 0)
		return (perror("minishell"));
	pid = fork();
	if (pid == 0)
	{
		get_input(endline, fd);
		close(fd[1]);
	}
	waitpid(pid, &status, 0);
	if (status == 1024)
		g_glbl.heredoc = 1;
	else
		g_glbl.heredoc = 0;
	close(fd[1]);
}
