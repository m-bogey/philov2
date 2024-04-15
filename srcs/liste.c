#include "mini_shell.h"	

t_minishell	*new_list()
{
	t_minishell	*new;

	new = malloc(sizeof(t_minishell));
	new->arg = NULL;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	return (new);
}

void	add_back(t_minishell *ms)
{
	t_minishell	*new;

	while (ms->next != NULL)
		ms = ms->next;
	new = new_list();
	ms->next = new;
}

/*bool_li	is_empty_list(t_li *li)
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
}*/