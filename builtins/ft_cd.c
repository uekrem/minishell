/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uguyildi <uguyildi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:27:02 by uguyildi          #+#    #+#             */
/*   Updated: 2023/08/17 13:27:03 by uguyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd_export(char *pwd, char *old_pwd)
{
	int	i;

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

void	change_pwd_env(char *pwd, char *old_pwd)
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
}

void	ft_cd_action(t_command *cmd)
{
	char	*tmp;
	char	pwd[1024];
	char	old_pwd[1024];

	getcwd(old_pwd, 1024);
	tmp = check_tilde(cmd->execute->next->value);
	if (chdir(tmp) != 0)
	{
		g_glbl.erorno = 1;
		cd_err(cmd->execute->value, cmd->execute->next->value);
	}
	else
		g_glbl.erorno = 0;
	free(tmp);
	getcwd(pwd, 1024);
	change_pwd_env(pwd, old_pwd);
	change_pwd_export(pwd, old_pwd);
}

void	ft_cd(t_command *cmd)
{
	char	*home;

	if (cmd->execute->next == 0)
	{
		home = getenv("HOME");
		if (home && *home)
			if (chdir(home))
				perror("minishell");
		return ;
	}
	ft_cd_action(cmd);
	g_glbl.erorno = 0;
}
