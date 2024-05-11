#include "mini_shell.h"

t_li_line	*new_list_pars(t_token *tok)
{
	t_li_line	*new;

	new = malloc(sizeof(t_li_line));
	new->token.str = tok->str;
	new->token.type = tok->type;
	new->next = NULL;
	return (new);
}

void	add_back_pars(t_li_line *li, t_token *tok)
{
	t_li_line	*new;

	while (li->next != NULL)
		li = li->next;
	new = new_list_pars(tok);
	li->next = new;
}

void	print_list_pars(t_li_line *li)
{
	while (li->next != NULL)
	{
	//	if (li->token.str[0] != '\0')
			printf("\033[0;32mstr = \033[0m%s \t \033[0;34mtype = \033[0m%d\n",li->token.str, li->token.type);
		li = li->next;
	}
	//printf("\n");
}

void	ft_free_li(t_li_line *li)
{
	while (li)
	{
		free(li->token.str);
		free(li);
		li = li->next;
	}
}