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
		break;
	}
	
	int	i;

	i = -1;
	//printf("sayi:%d\n", ft_str_shred(input));
	printf("ilk değer:%s ilk tipi:%d\n", list[1].value, list[1].type);
	while (++i < ft_str_shred(input))
		printf("%s  %u\n", list[i].value, list[i].type);
	return 0;
}
