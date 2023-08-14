#include "../minishell.h"

int     ft_how_far_chec(char c)
{
    if (((c >= 32 && c <= 47) 
			|| (c >= 58 && c <= 64)
			|| (c >= 91 && c <= 96)
			|| (c >= 123 && c <= 126)) 
			&& c)
			return (1);
    return (0);
}

char	*ft_env_null_orien(char *search, char *str, int *j, int temp)
{
	free(search);
	return (ft_env_null(str, j, temp));
}