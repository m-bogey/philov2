#include "mini_shell.h"

t_minishell	*new_list(void)
{
	t_minishell	*new;

	new = malloc(sizeof(t_minishell));
	new->arg = NULL;
	new->in = NULL;
	new->out = NULL;
	new->nb_arg = 0;
	new->nb_in = 0;
	new->nb_out = 0;
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

void	ft_free_ms(t_minishell *ms)
{
	while (ms)
	{
		free(ms->arg);
		free(ms->in);
		free(ms->out);
		free(ms);
		ms = ms->next;
	}
}
