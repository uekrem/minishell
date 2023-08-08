#include "minishell.h"

void	input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
			return ;
		else
			exit(errno);
	}
	dup2(fd, 0);
	close(fd);
}

void	output(char *file, int mode)
{
	int	fd;

	fd = 0;
	if (mode == OUT_FILE)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == D_INPUT_R)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
			return ;
		else
			exit(errno);
	}
	dup2(fd, 1);
	close(fd);
}