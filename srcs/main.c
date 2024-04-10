#include "mini_shell.h"
#include <string.h>

int		pre_execut(t_minishell *ms, char **envp);
void	execut(t_minishell *ms, char **envp);
void	redir_in(t_minishell *ms);
void	redir_out(t_minishell *ms);

void	init_struct(t_minishell *ms)
{
	int end = 2;

	ms->nb_elem = 2;
	ms->tmp_pipe = -1;
	ms->infile = -1;
	ms->outfile = -1;

	ms->arg = malloc(sizeof(char *) * 3);
	ms->arg[2] = NULL;
	ms->arg[0] = malloc(sizeof(char) * 4);
	ms->arg[0] = "cat\0";
	ms->arg[1] = malloc(sizeof(char) * 3);
	ms->arg[1] = "-e\0";
//	ms->arg[2] = malloc(sizeof(char) * 5);
//	ms->arg[2] = "file\0";

	ms->in = malloc(sizeof(char *) * 2);
	//ms->in[1] = malloc(sizeof(char) * 5);
	ms->in[end - 1] = NULL;
	ms->in[0] = malloc(sizeof(char) * 5);
	ms->in[0] = "Makefile\0";
	ms->out = malloc(sizeof(t_out *) * 2);

	ms->out[1] = NULL;
	ms->out[0] = malloc(sizeof(t_out) * 1);
	ms->out[0]->str = "test1\0";
	ms->out[0]->type = 1;

	ms->out = NULL;
	//ms->in = NULL;
}

// t_minishell	*get_struct_ms(t_li_line *li)
// {
// 	t_minishell	*ms;
// 	printf("\n\033[0;34m-----------------------\033[0m\n");
// 	print_list_pars(li);

// 	return (ms);
// }

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	(void)argv;
	char	*line;
	(void)line;
	t_li_line	*li;
	//t_minishell	*ms;

	// ms.nb_pipe = 1;
	// ms.nb_pipe = 0;
	//const char *path = getenv("PATH");
	while (1)
	{
 		line = readline("\001\e[34m\002\nm\e[32mi\e[36mn\e[35mi\e[31mshell$ \e[0m");
		li = parsing(line); //parsing thim
	 	printf("\n\033[0;34m-----------------------\033[0m\n");
	 	print_list_pars(li);
	//	ms = get_struct_ms(li);
	//	init_struct(&ms);
		// li = new_list(&ms);
		// add_back(li, &ms);
		// print_list(li);
	//	pre_execut(&ms, envp);
		//free struct 
	}
}

void	ft_close(t_minishell *ms)
{
	if (ms->infile != -1)
		close(ms->infile);
	if (ms->outfile != -1)
		close(ms->outfile);
	if (ms->fd[0] != -1)
		close(ms->fd[0]);
	if (ms->fd[1] != -1)
		close(ms->fd[1]);
}

int	pre_execut(t_minishell *ms, char **envp)
{
	int		i;

	i = 0;
	while (i < ms->nb_elem)
	{
		pipe(ms->fd);
		ms->pid = fork();
		if (ms->pid == 0)
			execut(ms, envp);
		else
		{
			close(ms->fd[1]);
			close(ms->infile);
			ms->tmp_pipe = ms->fd[0];
		}
		i++;
	}
	ft_close(ms);
	while (wait(0) > 0)
		;
	return (0);
}

void	execut(t_minishell *ms, char **envp)
{
	if (ms->in != NULL)
		redir_in(ms);
	else if (ms->tmp_pipe != -1)
		dup2(ms->tmp_pipe, 0);
	if (ms->out != NULL)
		redir_out(ms);
	else if (ms->nb_pipe > 0)
		dup2(ms->fd[1], 1);
	//ft_close(ms); voir ce aui doit etre close
	execve(cmd_path(ms->arg[0], envp), ms->arg, envp);
}

void	redir_in(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->in[i])
	{
		ms->infile = open(ms->in[0], O_RDONLY);
		i++;
	}
	dup2(ms->infile, 0);
	close(ms->infile);
}

void	redir_out(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->out[i])
	{
		if (ms->out[i]->type == 1)
			ms->outfile = open(ms->out[i]->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			ms->outfile = open(ms->out[i]->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		i++;
	}
	dup2(ms->outfile, 1);
	close(ms->outfile);
}
