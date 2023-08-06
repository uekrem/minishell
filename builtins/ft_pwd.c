#include "../minishell.h"

void	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, 1024);
	printf("%s\n", buf);
	if (!is_parent())
		exit(errno);
	g_glbl.erorno = 0;
}
