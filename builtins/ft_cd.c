#include "../minishell.h"

void	cd_err(char *value, char *str)
{
	write(2, "minishell: ", 11);
	write(2, value, ft_strlenn(value));
	write(2, ": ", 2);
	write(2, str, ft_strlenn(str));
	write(2, ": No such file or directory\n", 28);
	if (!is_parent())
		exit(errno);
}
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
			cd_err(cmd->execute->value, cmd->execute->next->value);
			//perror("minishell");
		}
		else
			g_glbl.erorno = 0;
		free(tmp);
	}
	else
	{
		home = getenv("HOME");
		if (home && *home)
			if (chdir(home))
				perror("minishell");
		g_glbl.erorno = 0;
	}
}
