#include "mini_shell.h"
#include <string.h>


int	get_struct_ms(t_li_line *li, t_minishell *ms, t_pipex *pipex)
{

 	printf("\n\033[0;34m-----------get_struct_ms------------\033[0m\n");
 //	print_list_pars(li);
	int			arg;
	t_li_line	*li_dup;
	int			index[3];
	t_minishell	*ms_dup;

	ms_dup = ms;
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	arg = 0;

	if (!li)
		return (0);
	li_dup = li;
	while (li_dup->next)
	{
		if (li_dup->token.type == 0 || li_dup->token.type == 1)
			arg++;
		if (li_dup->token.type == 2)
			ms_dup->nb_in++;
		if (li_dup->token.type == 3 || li_dup->token.type == 6)
			ms_dup->nb_out++;
		if (li_dup->token.type == 5)
		{
			pipex->nb_pipe++;
			ms_dup->arg = ft_calloc(sizeof(char *), (arg + 1));
			ms_dup->in = ft_calloc(sizeof(char *), (ms_dup->nb_in + 1));
			ms_dup->out = ft_calloc(sizeof(t_out), (ms_dup->nb_out + 1));
			arg = 0;
			add_back(ms_dup);
			ms_dup = ms_dup->next;
		}
		li_dup = li_dup->next;
	}
	ms_dup->arg = ft_calloc(sizeof(char *), (arg + 1));
	ms_dup->in = ft_calloc(sizeof(char *), (ms_dup->nb_in + 1));
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
		if (li->token.type == 2)
		{
			if (li->token.str[0] != '\0')
			{
				ms->in[index[1]] = li->token.str;
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
		while (ms->in[i])
		{
			dprintf(2, "in[%d] = %s\n", i, ms->in[i]);
			i++;
		}
		i = 0;
		while (ms->out[i].str)
		{
			dprintf(2, "out[%d] = %s\n", i, ms->out[i].str);
			i++;
		}
		dprintf(2, "nb in = %d    nb out = %d\n", ms->nb_in, ms->nb_out);
		ms = ms->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	//(void)envp;
	(void)argc;
	(void)argv;
	char	*line;
	(void)line;
	t_li_line	*li;
	t_minishell	*ms;
	t_pipex		pipex;

	//const char *path = getenv("PATH");
	while (1)
	{
 		line = readline("\001\e[34m\002\nm\e[32mi\e[36mn\e[35mi\e[31mshell$ \e[0m");
		add_history(line);
		init_struct(&pipex);
		li = parsing(line);
	 	printf("\n\033[0;34m------------main-----------\033[0m\n");
	 	print_list_pars(li);
		ms = new_list();
		get_struct_ms(li, ms, &pipex);
		printf("\nliste ms\n");
		print_ms(ms);
		printf("\n");
		pre_execut(ms, &pipex, envp);
		//free struct 
		free(line);
	}
}

