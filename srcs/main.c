#include "mini_shell.h"
#include <string.h>

int g_sig = 0;

static int	count_heredoc(t_minishell *ms, int heredoc_count, int i)
{
	int			r_value_hd;

	if (heredoc_count > 0)
	{
		ms->heredoc = ft_calloc(sizeof(char *), heredoc_count + 1);
		if (!ms->heredoc)
			return (1);
		ms->temp_name = ft_calloc(sizeof(char *), heredoc_count + 1);
		if (!ms->temp_name)
			return (1);
	}
	while (i <= heredoc_count && heredoc_count != 0)
	{
		r_value_hd = heredoc(ms, i);
		if (r_value_hd == 2)
		{
			unlink (ms->temp_name[i]);
			ms->in[i].str = NULL;
			return (1);
		}
		heredoc_count--;
		i++;
	}
	dprintf(2, "heredoc count : %d\n", heredoc_count);
	return (0);
}

int	get_struct_ms(t_li_line *li, t_minishell *ms, t_pipex *pipex)
{
 	printf("\n\033[0;34m-----------get_struct_ms------------\033[0m\n");
	t_li_line	*li_dup;
	int			index[3];
	t_minishell	*ms_dup;
	int			heredoc_count;
	int			i;

	ms_dup = ms;
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	heredoc_count = 0;
	i = 0;

	if (!li)
		return (0);
	li_dup = li;
	while (li_dup->next)
	{
		if ((li_dup->token.type == 0 || li_dup->token.type == 1) && li_dup->token.str[0] != '\0')
			ms_dup->nb_arg++;
		if ((li_dup->token.type == 2 || li_dup->token.type == 4) && li_dup->token.str[0] != '\0')
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
					dprintf(2, "mot de fin : %s\n", li->token.str);
					heredoc_count++;
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
			if (heredoc_count > 0)
			{
				count_heredoc(ms, heredoc_count, i);
				heredoc_count = 0;
			}
			index[0] = 0;
			index[1] = 0;
			index[2] = 0;
			ms = ms->next;
		}
		li = li->next;
	}
	if (heredoc_count > 0)
	{
		count_heredoc(ms, heredoc_count, i);
		//i++;
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
	(void)argc;
	(void)argv;
	char		*line;
	t_li_line	*li;
	t_minishell	*ms;
	t_pipex		pipex;
	t_li_line	*li_env;
	t_err		err;

	err.err = 0;
	li_env = liste_env(envp);
	while (1)
	{
		init_sig();
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_printf("exit\n");
			break;
		}
		add_history(line);
		init_struct(&pipex);
		if (pre_parsing(line) == 0)
		{
			li = parsing(line);
			free(line);
			expand(li, li_env, &err);
			remove_quote(li);
			printf("\n\033[0;34m------------main-----------\033[0m\n");
			print_list_pars(li);
			ms = new_list();
			get_struct_ms(li, ms, &pipex);
			printf("\nliste ms\n");
			printf("\n");
			pre_execut(ms, &pipex, li_env, li, &err);
			ft_free_li(li);
			ft_free_ms(ms);
			ft_printf("return value : %d\n", err.err);
		}
	}
	ft_free_li(li_env);
}
