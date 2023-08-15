#include "../minishell.h"

int	ft_strncmp2(const char *s1, const char *s2, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (s1[i] != s2[i])
			return (0);
	}
	if (s1[i])
		return (0);
	return (1);
}

char	*ft_sss(char *str)
{
	char	*temp;
	int		begin;
	int		i;

	i = 0;
	begin = 0;
	while (str[i] != '=' && str[i])
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	while (str[begin] != '=' && str[begin])
	{
		temp[begin] = str[begin];
		begin++;
	}
	temp[begin] = '\0';
	return (temp);
}

void	remove_export(char *del)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (g_glbl.export[i] != NULL)
	{
		temp = ft_sss(g_glbl.export[i]);
		if (ft_strncmp2(temp, del, ft_strlen(del, 0, '\0')))
		{
			j = i;
			free(g_glbl.export[i]);
			while (g_glbl.export[j] != NULL)
			{
				g_glbl.export[j] = g_glbl.export[j + 1];
				j++;
			}
			i = -1;
		}
		i++;
		free(temp);
	}
}

void	remove_env(char *del)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (g_glbl.env[i] != NULL)
	{
		temp = ft_sss(g_glbl.env[i]);
		if (ft_strncmp2(temp, del, ft_strlen(del, 0, '\0')))
		{
			j = i;
			free(g_glbl.env[j]);
			while (g_glbl.env[j] != NULL)
			{
				g_glbl.env[j] = g_glbl.env[j + 1];
				j++;
			}
			i = -1;
		}
		i++;
		free(temp);
	}
}

void	ft_unset(t_command *cmd)
{
	cmd->execute = cmd->execute->next;
	while (cmd->execute)
	{
		if (check_arg(cmd->execute->value, "unset"))
		{
			g_glbl.erorno = 1;
			break ;
		}
		remove_env(cmd->execute->value);
		remove_export(cmd->execute->value);
		cmd->execute = cmd->execute->next;
	}
	fill_paths();
}
