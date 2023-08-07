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

int	ft_builtins(t_command *cmd)
{
			if (which_commant(cmd->execute->value, "echo"))
				ft_echo(cmd);
			else if (which_commant(cmd->execute->value, "cd"))
				ft_cd(cmd);
			else if (which_commant(cmd->execute->value, "pwd"))
				ft_pwd();
			else if (which_commant(cmd->execute->value, "export"))
				ft_export(cmd);
			else if (which_commant(cmd->execute->value, "unset"))
				ft_unset(cmd);
			else if (which_commant(cmd->execute->value, "env"))
				ft_env(cmd);
			else if (which_commant(cmd->execute->value, "exit"))
				ft_exit(cmd);
			else
				return (0);
			return (1);
}
