#include "mini_shell.h"
#include <string.h>


int	get_struct_ms(t_li_line *li, t_minishell *ms, t_pipex *pipex)
{
 	printf("\n\033[0;34m-----------get_struct_ms------------\033[0m\n");
	t_li_line	*li_dup;
	int			index[3];
	t_minishell	*ms_dup;

	ms_dup = ms;
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;

	if (!li)
		return (0);
	li_dup = li;
	while (li_dup->next)
	{
		if ((li_dup->token.type == 0 || li_dup->token.type == 1) && li_dup->token.str[0] != '\0')
			ms_dup->nb_arg++;
		if (li_dup->token.type == 2 && li_dup->token.str[0] != '\0')
			ms_dup->nb_in++;
		if ((li_dup->token.type == 3 || li_dup->token.type == 6) && li_dup->token.str[0] != '\0')
			ms_dup->nb_out++;
		if (li_dup->token.type == 5)
		{
		
			pipex->nb_pipe++;
			ms_dup->arg = ft_calloc(sizeof(char *), (ms_dup->nb_arg + 1));
			ms_dup->arg[ms_dup->nb_arg] = NULL;
			ms_dup->in = ft_calloc(sizeof(t_out), (ms_dup->nb_in + 1));
			ms_dup->out = ft_calloc(sizeof(t_out), (ms_dup->nb_out + 1));
			add_back(ms_dup);
			ms_dup = ms_dup->next;
		}
		li_dup = li_dup->next;
	}
		dprintf(2, "\033[31mnb arg = %d nb in = %d  nb out = %d\n\033[0m",ms->nb_arg, ms->nb_in, ms->nb_out);
	ms_dup->arg = ft_calloc(sizeof(char *), (ms_dup->nb_arg + 1));
	ms_dup->arg[ms_dup->nb_arg] = NULL;
	ms_dup->in = ft_calloc(sizeof(t_out), (ms_dup->nb_in + 1));
	ms_dup->out = ft_calloc(sizeof(t_out), (ms_dup->nb_out + 1));
	while (li->next)
	{
		if (li->token.type == 0 || li->token.type == 1)
		{
			if (li->token.str[0] != '\0')
			{
				ms->arg[index[0]] = li->token.str;
				index[0]++;
			}
		}
		if (li->token.type == 2 || li->token.type == 4)
		{
			if (li->token.str[0] != '\0')
			{
				ms->in[index[1]].str = li->token.str;
				ms->in[index[1]].type = li->token.type;
				if (li->token.type == 4)
				{
					ms->heredoc = NULL;
					heredoc(ms);
				}
				index[1]++;
			}
		}
		if (li->token.type == 3 || li->token.type == 6)
		{
			if (li->token.str[0] != '\0')
			{
				ms->out[index[2]].str = li->token.str;
				ms->out[index[2]].type = li->token.type;
				index[2]++;
			}
		}
		if (li->token.type == 5)
		{
			index[0] = 0;
			index[1] = 0;
			index[2] = 0;
			ms = ms->next;
		}
		li = li->next;
	}
	return (0);
}

void	print_ms(t_minishell *ms)
{
	int	i;

	while (ms != NULL)
	{
		i = 0;
		while (ms->arg[i])
		{
			dprintf(2, "cmd[%d] = %s\n", i, ms->arg[i]);
			i++;
		}
		i = 0;
		while (ms->in[i].str)
		{
			dprintf(2, "in[%d] = %s\n", i, ms->in[i].str);
			i++;
		}
		i = 0;
		while (ms->out[i].str)
		{
			dprintf(2, "out[%d] = %s\n", i, ms->out[i].str);
			i++;
		}
		dprintf(2, "nb arg = %d nb in = %d  nb out = %d\n",ms->nb_arg, ms->nb_in, ms->nb_out);
		ms = ms->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	//(void)envp;
	(void)argc;
	(void)argv;
	char		*line;
	t_li_line	*li;
	t_minishell	*ms;
	t_pipex		pipex;
	t_li_line	*li_env;

	//const char *path = getenv("PATH");
	li_env = liste_env(envp);
	while (1)
	{
		//print_list_pars(env);
 		//line = readline("\001\e[34m\002\nm\e[32mi\e[36mn\e[35mi\e[31mshell$ \e[0m");
		line = readline("minishell$ ");
		add_history(line);
		init_struct(&pipex);
		li = parsing(line);
		free(line);
		expand(li, li_env);
		remove_quote(li);
	 	printf("\n\033[0;34m------------main-----------\033[0m\n");
	 	print_list_pars(li);
		ms = new_list();
		get_struct_ms(li, ms, &pipex);
		printf("\nliste ms\n");
	//	print_ms(ms);
		printf("\n");
		pre_execut(ms, &pipex, li_env);
		if (ms->temp_name)
			unlink(ms->temp_name);
		//free struct 
		//ft_free_li(li);
		//ft_free_ms(ms);
	}
}
