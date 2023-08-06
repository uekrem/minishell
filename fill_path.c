#include "minishell.h"

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

	if (g_glbl.path)
		free_paths(g_glbl.path);
	path = get_env_key("PATH");
	if (!(*path))
		g_glbl.path = NULL;
	else
		g_glbl.path = ft_split(path, ':');
	free(path);
}
