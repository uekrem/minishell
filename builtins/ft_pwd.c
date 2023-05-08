#include "../minishell.h"

void	ft_pwd(t_list *list, int *i)
{
	char	buf[1024];

	*i += 1;
	while (list[*i].type != END)
	{
		if (list[*i].type == PIPE)
			exit(0);
		*i += 1;
	}
	getcwd(buf, 1024);
	printf("%s\n", buf);
}
