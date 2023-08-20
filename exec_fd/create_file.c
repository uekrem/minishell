/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:26:30 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:03:18 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
		{
			g_glbl.erorno = 1;
			return (0);
		}
		else
			exit(1);
	}
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	output(char *file, int mode)
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
		{
			g_glbl.erorno = 1;
			return (0);
		}
		else
			exit(errno);
	}
	dup2(fd, 1);
	close(fd);
	return (1);
}
