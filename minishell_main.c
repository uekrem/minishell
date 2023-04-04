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
		list = malloc(sizeof(t_list) * ft_str_shred(input));
		list->env = env;
		ft_uname(input, list);
		ft_untype(input, list);
		ft_env_check(input, list);
		break;
	}
	
	printf("Value:%d\n", ft_str_shred(input));
	int	i;
	i = -1;
	while (++i < ft_str_shred(input))
		printf("%s	type:%d quates:%c\n", list[i].value, list[i].type,list[i].quates);
}
