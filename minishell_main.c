#include "minishell.h"

int	main()
{
	t_list		*list;
	char		*input;

	while(1)
	{
		input = readline("minishell: ");
		add_history(input);
		if (ft_opr_pair(input))
			return (0);
		list = malloc(sizeof(t_list) * ft_str_shred(input));
		ft_uname(input, list);
		//ft_untype(input, list);
		break;
	}
	printf("Value:%d\n", ft_str_shred(input));

	int	i;
	i = -1;
	while (++i < ft_str_shred(input))
		printf("%stype:%d\n", list[i].value, list[i].type); 
}
