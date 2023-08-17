/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:48 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:03:16 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dir(char *cmd)
{
	DIR	*dir;

	if (!cmd)
		exit(EXIT_SUCCESS);
	dir = opendir(cmd);
	if (dir && readdir(dir))
	{
		closedir(dir);
		directory_err(cmd);
	}
}

char	*mini_ret_free(char *mim, char *path)
{
	free(mim);
	return (path);
}

int	export_and_unset(char *str)
{
	if (ft_strncheck(str, "export", ft_strlenn(str)) == 0)
		return (1);
	if (ft_strncheck(str, "unset", ft_strlenn(str)) == 0)
		return (1);
	return (0);
}

void	command_err(char *str)
{
	errno = 127;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlenn(str));
	write(2, ": command not found\n", 20);
	if (!is_parent())
		exit(errno);
}

char	*get_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*new_cmd;

	check_dir(cmd);
	if (export_and_unset(cmd))
		exit(EXIT_SUCCESS);
	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = g_glbl.path;
	if (!paths)
		command_err(cmd);
	new_cmd = ft_strjoin("/", cmd);
	while (*paths)
	{
		path = ft_strjoin(*paths, new_cmd);
		if (!access(path, F_OK))
			return (mini_ret_free(new_cmd, path));
		free(path);
		paths++;
	}
	if (ft_strchr(cmd, '/'))
		no_file_err(cmd);
	free(new_cmd);
	return (NULL);
}
