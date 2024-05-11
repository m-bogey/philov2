#include "mini_shell.h"

static int	execut(t_minishell *ms, t_pipex *pipex, int i, t_li_line *li_env);
static int	redir_in(t_minishell *ms, t_pipex *pipex);
static int	redir_out(t_minishell *ms, t_pipex *pipex);
void		ft_close(t_pipex *pipex);

int		check_builtins(t_minishell *ms, t_li_line *li_env, char **env);

int	pre_execut(t_minishell *ms, t_pipex *pipex, t_li_line *li_env)
{
	int		i;
	char	**env;

	i = 0;
	env = liste_env_to_tab(li_env);
	if (check_builtins(ms, li_env, env) == 1 && pipex->nb_pipe == 0)
		return (0);
	free(env);
	while (i <= pipex->nb_pipe)
	{
		if (pipe(pipex->fd) == -1)
			return (-1);
		pipex->pid = fork();
		if (pipex->pid == -1)
			return (-1);
		if (pipex->pid == 0)
			execut(ms, pipex, i, li_env);
		else
		{
			close(pipex->fd[1]);
	//		close(pipex->infile);
	//		close(pipex->tmp_pipe);
			pipex->tmp_pipe = pipex->fd[0];
			ms = ms->next;
		}
		i++;
	}
	//close(pipex->tmp_pipe);
	//ft_close(pipex);
	while (wait(0) > 0)
		;
	return (0);
}

int		check_builtins(t_minishell *ms, t_li_line *li_env, char **env)
{
	if (ms->nb_arg == 0)
		return (0);
	if (ft_strcmp(ms->arg[0], "echo") == 0)
	{
		echo(ms);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "pwd") == 0)
	{
		pwd();
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "export") == 0)
	{
		export(ms, li_env, env);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "env") == 0)
	{
		envi(env);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "cd") == 0)
	{
		if (change_directory(ms, li_env) == -1)
			return (-1);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "exit") == 0)
		exit_minishell(1);
	if (ft_strcmp(ms->arg[0], "unset") == 0)
	{
		unset(li_env, ms);
		return (1);
	}
	return (0);
}

static int	execut(t_minishell *ms, t_pipex *pipex, int i, t_li_line *li_env)
{
	char	**env;
	int		return_value;

	close(pipex->fd[0]);
	if (ms->nb_in > 0)
	{
		return_value = redir_in(ms, pipex);
		if (return_value != 0)
			return (return_value);
	}
	else if (pipex->tmp_pipe != -1)
	{
		if (dup2(pipex->tmp_pipe, 0) == -1)
			return (-1);
		close(pipex->tmp_pipe);
	}
	if (ms->nb_out > 0)
	{
		return_value = redir_out(ms, pipex);
		if (return_value != 0)
			return (return_value);
	}
	else if (i < pipex->nb_pipe)
	{
		if (dup2(pipex->fd[1], 1) == -1)
			return (-1);
		close(pipex->fd[1]);
	}
	env = liste_env_to_tab(li_env);
	if (check_builtins(ms, li_env, env) == 1)
		return (0);
	//close(pipex->tmp_pipe);
	//ft_close(pipex); //voir ce aui doit etre close
	execve(cmd_path(ms->arg[0], env), ms->arg, env);
	exit(EXIT_FAILURE);
	return (0);
}

static int	redir_in(t_minishell *ms, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (ms->in[i].str && ms->in[i].type == 2)
	{
		pipex->infile = open(ms->in[0].str, O_RDONLY);
		if (pipex->infile == -1)
			return (126);
		i++;
	}
	if (dup2(pipex->infile, 0) == -1)
		return (-1);
	close(pipex->infile);
	return (0);
}

static int	redir_out(t_minishell *ms, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (ms->out[i].str)
	{
		if (ms->out[i].type == 6)
		{
			pipex->outfile = open(ms->out[i].str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (pipex->outfile == -1)
				return (126);
		}
		else
		{
			pipex->outfile = open(ms->out[i].str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (pipex->outfile == -1)
				return (126);
		}
		i++;
	}
	if (dup2(pipex->outfile, 1) == -1)
		return (-1);
	close(pipex->outfile);
	return (0);
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