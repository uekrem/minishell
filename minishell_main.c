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

t_link	*ft_copy_list(t_list *list)
{
	int		i;
	t_link	*link_block;
	t_link	*link_ls;

	i = 0;
	link_ls = NULL;
	while (i < list->list_len)
	{
		link_block = ft_lstnew(&list[i]);
		if (i == 0)
			link_block->prev=NULL;
		else
			link_block->prev= ft_lstlast(link_ls);
		ft_lstadd_back(&link_ls, link_block);
		i++;
	}
	return (link_ls);
}

int	main(int argc, char **argv, char **env)
{
	t_list		*list;
	t_link		*link;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	(void) cmd;
	(void) link;
	link = NULL;
	init_envair(env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_glbl.input = readline("minishell: ");
		add_history(g_glbl.input);
		ctrl_d(&g_glbl);
		if (ft_opr_pair(g_glbl.input))
			return (0);
		list = malloc(sizeof(t_list) * (ft_str_shred(g_glbl.input) + 1));
		list->flag = 0;
		list->list_len = ft_str_shred(g_glbl.input);
		ft_uname(list, g_glbl.input);
		ft_untype(list);
		ft_env_check(g_glbl.input, list);
		ft_appro_name(list);
		link = ft_copy_list(list);
		
		//ft_parse_eror(link);
		//ft_free(list); //çift freeleme kontrolü yapılmalı
		
		ft_fill_command(&cmd, link);
		// while (cmd)
		// {
		// 	while (cmd->execute)
		// 	{
		// 		printf("%s\n", cmd->execute->value);
		// 		cmd->execute = cmd->execute->next;
		// 	}
		// 	printf("***\n");
		// 	while (cmd->radi)
		// 	{
		// 		printf("%s\n", cmd->radi->value);
		// 		cmd->radi = cmd->radi->next;
		// 	}
		// 	printf("----------------\n");
		// 	cmd = cmd->next;
		// }
		// ft_builtins(list);
	}
}
