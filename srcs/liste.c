#include "mini_shell.h"	

t_li	*new_list(t_minishell *ms)
{
	t_li	*new;

	new = malloc(sizeof(t_li));
	new->ms = ms;
	new->next = NULL;
	return (new);
}

void	add_back(t_li *li, t_minishell *ms)
{
	t_li	*new;

	while (li->next != NULL)
		li = li->next;
	new = new_list(ms);
	li->next = new;
}

bool_li	is_empty_list(t_li *li)
{
	if(li == NULL)
		return (true);
	return (false);
}

int	list_length(t_li *li)
{
	int	size;

	size = 0;
	if(is_empty_list(li))
		return (size);
	while (li != NULL)
	{
		li = li->next;
		size++;
	}
	return (size);
}

void	print_list(t_li *li)
{
	if (is_empty_list(li))
	{
		printf("Rien a afficher, list vide");
		return;
	}
	while (li != NULL)
	{
		printf("%s\n",li->ms->arg[0]);
		li = li->next;
	}
	printf("\n");
}