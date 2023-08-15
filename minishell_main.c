#include "minishell.h"

t_glbl	g_glbl;

void	init_envair(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_glbl.env = malloc(sizeof(char *) * (i + 1));
	g_glbl.export = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		g_glbl.env[i] = ft_strdup(env[i]);
		g_glbl.export[i] = ft_strdup(env[i]);
		i++;
	}
	g_glbl.env[i] = NULL;
	g_glbl.export[i] = NULL;
}

void	free_execute(t_glbl *glbl)
{
	int	i;

	i = 0;
	while (glbl->env[i] != NULL)
		free(glbl->env[i++]);
	free(glbl->env);
	i = 0;
	while (glbl->export[i] != NULL)
		free(glbl->export[i++]);
	free(glbl->export);
	free(glbl->input);
}


int	ft_pipe_more(t_list *list)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	if  (list[0].type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		g_glbl.erorno = 258;
		ft_free(list);
		return (1);
	}
	while (list[++i].value)
	{
		if (list[i].type == PIPE && flag == 0)
			flag = 1;
		else if (list[i].type == PIPE && flag == 1)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			g_glbl.erorno = 258;
			ft_free(list);
			return (1);
		}
		else if (list[i].type != PIPE && flag == 1)
			flag = 0;
	}
	return (0);
}

void	ft_free_link(t_link **link)
{
	t_link	*root;

	if (!*link)
		return ;
	while (*link != NULL)
	{
		root = (*link)->next;
		free((*link)->value);
		free(*link);
		*link = root;
	}
	free(*link);
}

void	ft_free_radi(t_radira *radi)
{
	t_radira	*temp;

	if (!radi)
		return;
	while (radi)
	{
		temp = radi->next;
		free(radi);
		radi = temp;
	}
	free(radi);
}

void	ft_free_exec(t_execute *exec)
{
	t_execute	*temp;

	if (!exec)
		return;
	while (exec)
	{
		temp = exec->next;
		free(exec);
		exec = temp;
	}
	free(exec);
}

void	ft_free_cmd()
{
	t_command *temp_e;
	int	i;

	i = -1;
	while (++i < g_glbl.cmd_count)
	{
		temp_e = g_glbl.cmd->next;
		ft_free_radi(g_glbl.cmd->radi);
		ft_free_exec(g_glbl.cmd->execute);
		free(g_glbl.cmd);
		g_glbl.cmd = temp_e;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_list		*list;
	t_link		*link;

	(void)argc;
	(void)argv;
	(void) link;
	link = NULL;
	init_envair(env);
	signal_init();
	fill_paths();
	g_glbl.erorno = 0;
	while (1)
	{
		//system("leaks minishell");
		g_glbl.parent_pid = 1;
		g_glbl.input = readline("minishell: ");
		add_history(g_glbl.input);
		ctrl_d(&g_glbl);
		if (ft_opr_pair(g_glbl.input))
			continue;
		list = malloc(sizeof(t_list) * (ft_str_shred(g_glbl.input) + 1));
		list->flag = 0;
		g_glbl.flag = 0;
		g_glbl.cmd_count = 0;
		g_glbl.heredoc = 0;
		list->list_len = ft_str_shred(g_glbl.input);
		ft_uname(list, g_glbl.input);
		ft_untype(list);
		ft_env_check(g_glbl.input, list);		
		ft_appro_name(list);
		if(ft_pipe_more(list))
			continue;
		link = ft_copy_list(list);
		if(ft_parse_eror(link))
		{
			ft_free_link(&link);
			free(list);
			free(g_glbl.input);
			continue;
		}
		if(ft_fill_command(link))
		{
			ft_free_cmd();
			ft_free_link(&link);
			free(list);
			free(g_glbl.input);
			continue;
		}
		run_cmd();
		ft_free_cmd();
		ft_free_link(&link);
		free(list);
		free(g_glbl.input);
	}
}
