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

void	ft_builtins(char *input, t_list *list)
{
	int	i;

	i = 0;
	while (i < ft_str_shred(input))
	{
		if (list[i].type == COMMAND)
		{
			if (which_commant(list, &i, "echo"))
				ft_echo(input, list);
			else if (which_commant(list, &i, "cd"))
				ft_cd(list);
			else if (which_commant(list, &i, "pwd"))
				ft_pwd();
			else if (which_commant(list, &i, "export"))
				ft_export(list);
			else if (which_commant(list, &i, "unset"))
				printf("unset fonksiyonu çalıştı");
			else if (which_commant(list, &i, "env"))
				printf("env fonksiyonu çalıştı");
			else if (which_commant(list, &i, "exit"))
				printf("exit fonksiyonu çalıştı");
		}
		i++;
	}
}
