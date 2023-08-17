/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:42 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 14:38:53 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncheck(const char *s1, const char *s2, size_t n)
{
	unsigned char	*x;
	unsigned char	*y;
	size_t			i;

	x = (unsigned char *)s1;
	y = (unsigned char *)s2;
	i = 0;
	while ((x[i] != '\0' || y[i] != '\0') && i < n)
	{
		if (x[i] > y[i])
			return (x[i] - y[i]);
		else if (x[i] < y[i])
			return (x[i] - y[i]);
		i++;
	}
	if (!x[i] || !y[i])
		return (1);
	return (0);
}

char	*split_env(char *str)
{
	while (*str != '=')
		str++;
	str++;
	return (ft_strdup(str));
}

char	*get_env_key(char *str)
{
	size_t	len;
	char	**env;
	char	*new_str;

	env = g_glbl.env;
	new_str = ft_strjoin(str, "=");
	len = ft_strlenn(new_str);
	while (*env)
	{
		if (!ft_strncmp(*env, new_str, len))
		{
			free(new_str);
			return (split_env(*env));
		}
		env++;
	}
	free(new_str);
	return (ft_calloc(sizeof(char *), 1));
}

void	free_paths(char **paths)
{
	size_t	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	fill_paths(void)
{
	char	*path;

	path = NULL;
	if (g_glbl.path)
		free_paths(g_glbl.path);
	path = get_env_key("PATH");
	if (!(*path))
		g_glbl.path = NULL;
	else
		g_glbl.path = ft_split(path, ':');
	free(path);
}
