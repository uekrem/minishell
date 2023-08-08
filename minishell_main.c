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


int	ft_sil(t_list *list)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (list[i].value)
	{
		while (list[i].type == PIPE && list[i].type != END){
			flag++;
			i++;
		}
		if (flag > 2)
		{
			printf("syntax error near unexpected token `");
			printf("|");
			if (flag > 3)
				printf("|");
			printf("'\n");
			return (1);
		}
		if (list[i].type == END)
			return(0);
		i++;
	}
	return (0);
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
		g_glbl.parent_pid = 1;
		g_glbl.input = readline("minishell: ");
		add_history(g_glbl.input);
		ctrl_d(&g_glbl);
		if (ft_opr_pair(g_glbl.input))
			return (0);
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
		//if(ft_sil(list))	//düzelt ama çalışıyo (problem yok)
		//	continue;
		link = ft_copy_list(list);
		if(ft_parse_eror(link))
			continue;
		ft_fill_command(link);
		//printf("%s\n", g_glbl.cmd->execute->value);
		run_cmd();
		// while (g_glbl.cmd)
		// {
		// 	while (g_glbl.cmd->execute)
		// 	{
		// 		printf("%s\n", g_glbl.cmd->execute->value);
		// 		g_glbl.cmd->execute = g_glbl.cmd->execute->next;
		// 	}
		// 	printf("***\n");
		// 	while (g_glbl.cmd->radi)
		// 	{
		// 		printf("%s\n", g_glbl.cmd->radi->value);
		// 		g_glbl.cmd->radi = g_glbl.cmd->radi->next;
		// 	}
		// 	printf("----------------\n");
		// 	g_glbl.cmd = g_glbl.cmd->next;
		// }
		//continue;
		ft_free(list);
	}
}
