/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:50 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 15:31:28 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_words(char *str1, char *str2)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (!str1[0] && !str2[0])
		return (1);
	while (str1[j])
	{
		k = 0;
		if (str1[j] == str2[k])
		{
			if (equal_process(str1, str2, &j, &k))
				return (1);
		}
		if (str1[j] != '\0')
			j++;
	}
	return (0);
}

void	interreput(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(errno);
}

void	get_input(char *endline, int *fd)
{
	char	*input;

	signal(SIGINT, interreput);
	while (1)
	{
		input = readline("heredoc>> ");
		if (heredoc_words(input, endline)
			&& ft_strlenn(input) == ft_strlenn(endline))
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
