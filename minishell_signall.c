#include "minishell.h"

void	ctrl_d(t_glbl *glbl)
{
	if (!glbl->input)
	{
		printf("\nexit\n");
		free_execute(glbl);
		exit(0);
	}
}