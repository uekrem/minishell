#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_list		*list;
	char		*input;

	(void)argc;
	(void)argv;
	while(1)
	{
		input = readline("minishell: ");
		add_history(input);
		if (ft_opr_pair(input))
			return (0);
		list = malloc(sizeof(t_list) * (ft_str_shred(input) + 1));
		list->env = env;
		list->flag = 0;
		list->list_len = ft_str_shred(input);
		ft_uname(input, list);
		ft_appro_name(list);
		ft_untype(input, list);
		ft_env_check(input, list);
		ft_builtins(input, list);
	}

	// printf("list range:%d\n", ft_str_shred(input));

	// int	i;
	// i = -1;
	// while (++i < ft_str_shred(input))
	// 	printf("value:%s type: %d\n", list[i].value, list[i].type);
}
