/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:45 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:03:47 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_parent(void)
{
	return (g_glbl.parent_pid);
}

void	no_file_err(char *str)
{
	if (ft_strchr(str, '/'))
		errno = 127;
	else
		errno = 1;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlenn(str));
	write(2, ": No such file or directory\n", 28);
	if (!is_parent())
		exit(errno);
}

void	directory_err(char *str)
{
	errno = 126;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlenn(str));
	write(2, ": is a directory\n", 17);
	if (!is_parent())
		exit(errno);
}
