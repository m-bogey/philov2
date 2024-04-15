#include "mini_shell.h"

void	execut(t_minishell *ms, t_pipex *pipex, char **envp, int i);
void	redir_in(t_minishell *ms, t_pipex *pipex);
void	redir_out(t_minishell *ms, t_pipex *pipex);
void	ft_close(t_pipex *pipex);

int	pre_execut(t_minishell *ms, t_pipex *pipex, char **envp)
{
	int		i;

	i = 0;
	while (i <= pipex->nb_pipe)
	{
		pipe(pipex->fd);
		pipex->pid = fork();
		if (pipex->pid == 0)
			execut(ms, pipex, envp, i);
		else
		{
			close(pipex->fd[1]);
			close(pipex->infile);
			pipex->tmp_pipe = pipex->fd[0];
			ms = ms->next;
		}
		i++;
	}
	ft_close(pipex);
	while (wait(0) > 0)
		;
	return (0);
}

void	execut(t_minishell *ms, t_pipex *pipex, char **envp, int i)
{
	if (ms->in != NULL)
		redir_in(ms, pipex);
	else if (pipex->tmp_pipe != -1)
		dup2(pipex->tmp_pipe, 0);
	if (ms->out != NULL)
		redir_out(ms, pipex);
	else if (i < pipex->nb_pipe)
		dup2(pipex->fd[1], 1);
	ft_close(pipex); //voir ce aui doit etre close
	execve(cmd_path(ms->arg[0], envp), ms->arg, envp);
}

void	redir_in(t_minishell *ms, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (ms->in[i])
	{
		pipex->infile = open(ms->in[0], O_RDONLY);
		i++;
	}
	dup2(pipex->infile, 0);
	close(pipex->infile);
}

void	redir_out(t_minishell *ms, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (ms->out[i].str)
	{
		if (ms->out[i].type == 6)
			pipex->outfile = open(ms->out[i].str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			pipex->outfile = open(ms->out[i].str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		i++;
	}
	dup2(pipex->outfile, 1);
	close(pipex->outfile);
}

void	ft_close(t_pipex *pipex)
{
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
}