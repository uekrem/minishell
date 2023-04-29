#include "../minishell.h"

int	arg_count(t_list *list)
{
	int	i;

	i = 0;

	while (list[i].value)
		i++;
	if (i > 2)
		return (1);
	else if (i == 1)
		return (-1);
	return (0);
}

void	ft_cd(t_list *list)
{
	char	*str;

	if (arg_count(list) == 1)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (arg_count(list) == -1)
	{
		printf("env HOME coment\n");
		return ;
	}
	if (chdir(list[1].value) == -1)
	{
		str = strerror(errno);
		printf("Minishell: cd: %s %s\n",list[1].value, str);
	}
}
