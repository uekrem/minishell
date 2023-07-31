#include "../minishell.h"

int	which_commant(char *str1, char *str2)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (str1[j])
	{
		k = 0;
		if (str1[j] == str2[k])
		{
			while (str1[j] == str2[k] && str1[j] != '\0' &&
				str2[k] != '\0')
			{
				if (str1[j] != '\0')
					j++;
				if (str2[k] != '\0')
					k++;
			}
			if (str1[j] == '\0' && str2[k] == '\0')
				return (1);
		}
		if (str1[j] != '\0')
			j++;
	}
	return (0);
}

void	ft_builtins()
{

			if (which_commant(g_glbl.cmd->execute->value, "echo"))
				ft_echo(g_glbl.cmd);
			else if (which_commant(g_glbl.cmd->execute->value, "cd"))
				ft_cd(g_glbl.cmd);
			else if (which_commant(g_glbl.cmd->execute->value, "pwd"))
				ft_pwd();
			else if (which_commant(g_glbl.cmd->execute->value, "export"))
				ft_export(g_glbl.cmd);
			else if (which_commant(g_glbl.cmd->execute->value, "unset"))
				ft_unset(g_glbl.cmd);
			else if (which_commant(g_glbl.cmd->execute->value, "env"))
				ft_env(g_glbl.cmd);
			else if (which_commant(g_glbl.cmd->execute->value, "exit"))
				ft_exit(g_glbl.cmd);
}
