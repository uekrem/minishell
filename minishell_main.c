#include "minishell.h"

t_glbl g_glbl;

void init_envair(char **env)
{
	int  i;

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
int	main(int argc, char **argv, char **env)
{
	t_list		*list;

	(void)argc;
	(void)argv;
	init_envair(env);
	signal(SIGQUIT, SIG_IGN);
	while(1)
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
		ft_env_check(g_glbl.input, list);
		ft_appro_name(list);
		ft_untype(list);
		ft_builtins(list);
		int	i;

		i = -1;
		while (++i < list->list_len)
			printf("%s %d\n", list[i].value, list[i].type);
		ft_free(list, g_glbl.input);
		//system("leaks minishell");
	}
}
