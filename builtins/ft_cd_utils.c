#include "../minishell.h"

void	cd_err(char *value, char *str)
{
	write(2, "minishell: ", 11);
	write(2, value, ft_strlenn(value));
	write(2, ": ", 2);
	write(2, str, ft_strlenn(str));
	write(2, ": No such file or directory\n", 28);
	if (!is_parent())
		exit(errno);
}

char	*check_tilde(char *str)
{
	if (!ft_strlenn(str) || *str != '~' || !getenv("HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(getenv("HOME"), str));
}
