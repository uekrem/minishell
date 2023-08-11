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
void	change_pwd(char *pwd, char *old_pwd)
{
	int	i;

	i = -1;
	while (g_glbl.env[++i])
	{
		if (ft_strncmp(g_glbl.env[i], "PWD=", 4) == 0)
		{
			free(g_glbl.env[i]);
			g_glbl.env[i] = ft_strjoin("PWD=", pwd);
		}
		if (ft_strncmp(g_glbl.env[i], "OLDPWD=", 7) == 0)
		{
			free(g_glbl.env[i]);
			g_glbl.env[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
	}
	i = -1;
	while (g_glbl.export[++i])
	{
		if (ft_strncmp(g_glbl.export[i], "PWD=", 4) == 0)
		{
			free(g_glbl.export[i]);
			g_glbl.export[i] = ft_strjoin("PWD=", pwd);
		}
		if (ft_strncmp(g_glbl.export[i], "OLDPWD=", 7) == 0)
		{
			free(g_glbl.export[i]);
			g_glbl.export[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
	}
}

void ft_cd(t_command *cmd)
{
	char	*home;
	char	*tmp;
	char	pwd[1024];
	char	old_pwd[1024];

	if (cmd->execute->next == 0)
	{
		home = getenv("HOME");
		if (home && *home)
			if (chdir(home))
				perror("minishell");
		return ;
	}
	getcwd(old_pwd, 1024);
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
	getcwd(pwd, 1024);
	change_pwd(pwd, old_pwd);
	g_glbl.erorno = 0;
}
