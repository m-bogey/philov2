#include "mini_shell.h"

void	config_liste(t_li_line *li);

t_li_line	*new_list_pars(t_token *tok);
void	add_back_pars(t_li_line *li, t_token *tok);
void	print_list_pars(t_li_line *li);

void	remove_elem_liste(t_li_line *li)
{
	t_li_line	*tmp;

	while (li->next != NULL)
	{
		if (li->next->token.str == )
		tmp = li->next;
	}


}

t_li_line	*parsing(char *line)
{
	t_li_line	*li;
	t_token		token;

	token = ft_strtok(line, " \t<>|");
	li = new_list_pars(&token);
	while (token.str)
	{
		token = ft_strtok(NULL, " \t<>|");
		add_back_pars(li, &token);
	}
	config_liste(li);
	remove_elem_liste(li);
	return (li);
}

void	config_liste(t_li_line *li)
{
	t_li_line	*tmp;

	tmp = li;
	print_list_pars(li);
	while (li->next != NULL)
	{
		if (li->token.type == 2)
		{
			if (li->next->token.type == 2)
			{
				li = li->next;
				li->next->token.type = 4;
			}
			else
				li->next->token.type = 2;
			li = li->next;
		}
		if (li->token.type == 3)
		{
			if (li->next->token.type == 3)
			{
				li = li->next;
				li->next->token.type = 6;
			}
			else
				li->next->token.type = 3;
			li = li->next;
		}
		li = li->next;
	}
	printf("\n\033[0;31m--------------------------\033[0m\n");
	print_list_pars(tmp);
}

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
		if (li->token.str[0] != '\0')
			printf("\033[0;32mstr = \033[0m%s \t \033[0;34mtype = \033[0m%d\n",li->token.str, li->token.type);
		li = li->next;
	}
	//printf("\n");
}