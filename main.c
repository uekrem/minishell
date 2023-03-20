#include "minishell.h"

int	main()
{
	t_list		*list;
	char		*input;

	while(1)
	{
		input = readline("minishell: ");
		add_history(input);
		list = malloc(sizeof(list) * ft_str_shred(input));
		ft_uname(input, list);
	}
	return 0;
}
