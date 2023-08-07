#include "../minishell.h"

void	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, 1024);
	printf("%s\n", buf);
}
