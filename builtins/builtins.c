#include "../minishell.h"

int	which_commant(char *str1, char *str2)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (!str1)
		return (0);
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
	t_command *newcmd;

	newcmd = cmd;
	if (newcmd->execute == NULL)
		return (0);
	if (which_commant(newcmd->execute->value, "echo"))
		ft_echo(newcmd);
	else if (which_commant(newcmd->execute->value, "cd"))
		ft_cd(newcmd);
	else if (which_commant(newcmd->execute->value, "pwd"))
		ft_pwd();
	else if (which_commant(newcmd->execute->value, "export"))
		ft_export(newcmd);
	else if (which_commant(newcmd->execute->value, "unset"))
		ft_unset(newcmd);
	else if (which_commant(newcmd->execute->value, "env"))
		ft_env(newcmd);
	else if (which_commant(newcmd->execute->value, "exit"))
		ft_exit(newcmd);
	else
		return (0);
	return (1);
}
