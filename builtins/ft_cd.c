#include "../minishell.h"

char	*check_tilde(char *str)
{
	if (!ft_strlenn(str) || *str != '~' || !getenv("HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(getenv("HOME"), str));
}

void ft_cd(t_command *cmd)
{
	char	*home;
	char	*tmp;

	if (cmd->execute->next != 0)
	{
		tmp = check_tilde(cmd->execute->next->value);
		if (chdir(tmp) != 0)
		{
			g_glbl.erorno = 1;
			perror("minishell ");
		}
		else
			//g_glbl.erorno = 0;
		free(tmp);
	}
	else
	{
		home = getenv("HOME");
		if (home && *home)
			if (chdir(home))
				perror("minishell ");
		//g_glbl.erorno = 0;
	}
}
