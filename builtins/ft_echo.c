#include "../minishell.h"

void ft_input_r(t_list *list, int *i)
{
	int fd;
	if (list[*i].type == OUTPUT_R)
	{
		fd = open(list[*i + 1].value, O_CREAT | O_RDWR | O_TRUNC, 0777);
		int j;
		j = 0;
		while (list[j].type)
		{
			if (list[j].type != ARG)
				j++;
			else
			{
				ft_putstr_fd(list[j].value, fd);
				if(list[j + 1].type != END)
					write(fd, " ", 1);
				j++;
			}
		}
		if (list->flag == 0)
			write(fd, "\n", 1);
		close(fd);
	}
	else
	{
		fd = open(list[*i + 1].value, O_RDWR);
		if (fd == -1)
		{
			printf("Minishell: %s: No such file or directory\n", list[*i + 1].value);
		}
		while (list[*i].type != COMMAND)
			*i -= 1;
		while (list[*i].type)
		{
			if (list[*i].type != ARG)
				*i += 1;
			else
			{
				printf("%s",list[*i].value);
				if(list[*i + 1].type != END)
					printf(" ");
				*i+=1;
			}
		}
		if (list->flag == 0)
			printf("\n");
	}
}

void	ft_echo(t_list *list, int *i)
{
	*i += 1;
	if (!list[*i].value)
	{
		printf("\n");
		return;
	}
	while (*i < list->list_len)
	{
		if (list[*i].type == PIPE)
			exit (0);
		else if (list[*i].value[0] == '-' &&list[*i].value[1] == 'n' && !list[*i].value[2])
		{
			list[*i].type = FLAG;
			list->flag = 1;
		}
		else if (list[*i].type == INPUT_R || list[*i].type == OUTPUT_R)
			ft_input_r(list, i);
		*i += 1;
	}

	*i = 1;
	while (list[*i].type != END)
	{
		if (list[*i].type == ARG)
		{
			printf("%s",list[*i].value);
			if (list[*i + 1].type != END)
				printf(" ");
		}
		*i += 1;
	}
	if (list->flag == 0)
		printf("\n");

}
