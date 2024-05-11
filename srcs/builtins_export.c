#include "mini_shell.h"

static void	sort_tab(char **env)
{
	size_t	i;
	char	*tmp;
	int		swapped;

	i = 0;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		while (env[i + 1] != NULL) 
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				swapped = 1;
				i = 0;
			}
			i++;
		}
	}
}

static void	print_export(char **env)
{
	size_t	i;

	i = 0;
	sort_tab(env);
	while (env[i])
	{
		if (env[i][0] != '\0')
			ft_printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	export(t_minishell *ms, t_li_line *li_env, char **env)
{
	size_t		i;
	t_token		token;
	t_li_line	*li_begin;

	li_begin = li_env;
	if (ms->arg[1] == NULL)
		return (print_export(env));
	i = 1;
	while (ms->arg[i])
	{
		while (li_env)
		{
			if (ft_strcmp(ms->arg[i], li_env->token.str) == 0)
			{
				free(li_env->token.str);
				li_env->token.str = ft_strdup(ms->arg[i]);
				return ;
			}
			li_env = li_env->next;
		}
		li_env = li_begin;
		token.str = ft_strdup(ms->arg[i]);
		add_back_pars(li_env, &token);
		i++;
	}
}
