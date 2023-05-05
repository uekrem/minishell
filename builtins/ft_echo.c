#include "../minishell.h"

void ft_input_r(t_list *list, int *i)
{
	int fd;

	fd = open(list[*i + 1].value, O_RDWR);
	if (fd == -1)
	{
		printf("Minishell: %s: No such file or directory\n", list[*i + 1].value);
	}
	else
	{
		while (list[*i].type != COMMAND)
			*i -= 1;
		while (list[*i].type)
		{
			if (list[*i].type != ARG)
				*i += 1;
			else
			{
				printf("%s",list[*i].value);
				printf(" ");
				*i+=1;
			}
		}
		printf("\n");
	}
}

void	ft_echo(char *input, t_list *list, int *i)
{
	*i += 1;
	while (*i < ft_str_shred(input))
	{
		if (list[*i].type == PIPE)
			exit (0);
		else if (list[*i].type == INPUT_R || list[*i].type == OUTPUT_R)
		{
			if (list[*i].type == INPUT_R)
				ft_input_r(list, i);
		}
		*i += 1;
	}
}
