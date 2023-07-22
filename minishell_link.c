#include "minishell.h"

t_link	*ft_lstlast(t_link *lst)
{
	while (lst != NULL && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_link **lst, t_link *new)
{
	t_link	*position;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		position = ft_lstlast(*lst);
		position->next = new;
	}
}

t_link	*ft_lstnew(t_list *list)
{
	t_link	*root;

	root = (t_link *)malloc(sizeof(t_link));
	if (!root)
		return (0);
	root->value = list->value;
	root->type = list->type;
	root->list_len = list->list_len;
	root->flag = list->flag;
	root->next = NULL;
	return (root);
}