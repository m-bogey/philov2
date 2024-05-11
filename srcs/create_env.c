#include "mini_shell.h"

t_li_line	*liste_env(char **envp)
{
	size_t	i;
	t_li_line *liste_env;
	t_token		token;

	i = 1;
	token.str = ft_strdup(envp[0]);
	token.type = 0;
	liste_env = new_list_pars(&token);
	while (envp[i])
	{
		token.str = ft_strdup(envp[i]);
		token.type = 0;
		add_back_pars(liste_env, &token);
		i++;
	}
	return (liste_env);
}

size_t	count_liste(t_li_line *list)
{
	size_t	i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**liste_env_to_tab(t_li_line *li_env)
{
	size_t	size;
	size_t	i;
	char	**env;

	i = 0;
	size = count_liste(li_env);
	env = malloc(sizeof(char *) * (size + 1));
	//protec
	env[size] = NULL;
	while (li_env != NULL)
	{
		env[i] = li_env->token.str;
		i++;
		li_env = li_env->next;
	}

	return (env);
}