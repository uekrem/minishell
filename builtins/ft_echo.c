#include "../minishell.h"

void	ft_echo(char *input, t_list *list)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (i < ft_str_shred(input))
	{
		if (list[i].value[1] == 'n' || list[i].value[0] == '-') //Düzeltilecek 
		{
			flag = 1;											//argümana göre bakılacak 
			i++;
		}
		printf("%s", list[i].value);
		i++;
	}
	if (flag != 1)
		printf("\n");
}
