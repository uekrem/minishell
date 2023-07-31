#include "../minishell.h"

void	free_env(void)
{
	int	i;

	i = 0;
	while (g_glbl.env[i])
	{
		free(g_glbl.env[i]);
		i++;
	}
	free(g_glbl.env);
}

void	remove_env(char *del)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (g_glbl.env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (g_glbl.env[i])
	{
		if (ft_strncmp(g_glbl.env[i], del, ft_strlenn(del)))
		{
			new_env[j] = ft_strdup(g_glbl.env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_env();
	g_glbl.env = new_env;
}

void	ft_unset(t_command *cmd)
{
	cmd->execute = cmd->execute->next;
	while (cmd->execute)
	{
		remove_env(cmd->execute->value);
		cmd->execute = cmd->execute->next;
	}
}