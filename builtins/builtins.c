#include "../minishell.h"

int	which_commant(t_list *list, int *i,char *str)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (list[*i].value[j])
	{
		k = 0;
		if (list[*i].value[j] == str[k])
		{
			while (list[*i].value[j] == str[k] && list[*i].value[j] != '\0' &&
				str[k] != '\0')
			{
				if (list[*i].value[j] != '\0')
					j++;
				if (str[k] != '\0')
					k++;
			}
			if (list[*i].value[j] == '\0' && str[k] == '\0')
				return (1);
		}
		if (list[*i].value[j] != '\0')
			j++;
	}
	return (0);
}

void	ft_builtins(t_list *list)
{
	int	i;

	i = 0;
	while (i < list->list_len)
	{
		if (list[i].type == COMMAND)
		{
			if (which_commant(list, &i, "echo"))
				ft_echo(list, &i);
			else if (which_commant(list, &i, "cd"))
				ft_cd(list, &i);
			else if (which_commant(list, &i, "pwd"))
				ft_pwd(list, &i);
			else if (which_commant(list, &i, "export"))
				ft_export(list);
			else if (which_commant(list, &i, "unset"))
				ft_unset(list, &i);
			else if (which_commant(list, &i, "env"))
				ft_env(list);
			else if (which_commant(list, &i, "exit"))
				printf("exit fonksiyonu çalıştı");
		}
		i++;
	}
}
