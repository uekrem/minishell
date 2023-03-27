#include "minishell.h"

int	main()
{
	t_list		*list;
	char		*input;

	while(1)
	{
		input = readline("minishell: ");
		add_history(input);
		list = malloc(sizeof(t_list) * ft_str_shred(input));
		ft_uname(input, list);
		//ft_untype(input, list);
		break;
	}
	
	int	i;
	i = -1;
	printf("kelime:%d\n", ft_str_shred(input));
	while (++i < ft_str_shred(input))
		printf("%s	type:%d\n", list[i].value, list[i].type); 
	return 0;
}
