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

int	main(int argc, char **argv, char **env)
{
	t_list		*list;
	char		*input;

	(void)argc;
	(void)argv;
	init_envair(env);
	while(1)
	{
		input = readline("minishell: ");
		add_history(input);
		if (ft_opr_pair(input))
			return (0);
		list = malloc(sizeof(t_list) * (ft_str_shred(input) + 1));
		list->flag = 0;
		list->list_len = ft_str_shred(input);
		ft_uname(list, input);
		ft_env_check(input, list);
		ft_appro_name(list);
		ft_untype(list);
		ft_builtins(input, list);
		int	i;
		 i = -1;
		 while (++i < ft_str_shred(input))
		 	printf("value:%s type:%u\n", list[i].value, list[i].type);
	}
}
