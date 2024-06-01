#include "mini_shell.h"

static int	execut(t_minishell *ms, t_pipex *pipex, int i, t_li_line *li_env, t_li_line *li, t_err *err);
static int	redir_in(t_minishell *ms, t_pipex *pipex, t_err *err);
static int	redir_out(t_minishell *ms, t_pipex *pipex, t_err *err);
void		ft_close(t_pipex *pipex);

int		check_builtins(t_minishell *ms, t_li_line *li_env, char **env, t_li_line *li, t_err *err);

int	pre_execut(t_minishell *ms, t_pipex *pipex, t_li_line *li_env, t_li_line *li, t_err *err)
{
	int		i;
	char	**env;
	int		status;

	i = 0;
	env = liste_env_to_tab(li_env);
	if (pipex->nb_pipe == 0 && check_builtins(ms, li_env, env, li, err) == 1)
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
		{
			fork_sig();
			if (execut(ms, pipex, i, li_env, li, err) == -1)
				return(-1);
			exit(1);
		}
		else
		{
			close(pipex->fd[1]);
			if (pipex->infile != -1)
				close(pipex->infile);
			if (pipex->tmp_pipe != -1)
				close(pipex->tmp_pipe);
			pipex->tmp_pipe = pipex->fd[0];
			ms = ms->next;
		}
		i++;
	}
	//close(pipex->tmp_pipe);
	//ft_close(pipex);
	exec_sig ();
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_sig = 0;
		;
	}
	if (g_sig == SIGQUIT)    // AJOUTE PEUT ETRE DU \n POUR LE CTRL C ICI A VOIR
		write (2, "Quit (core dumped)\n", 19);
	g_sig = 0;
	return (0);
}

int	check_builtins(t_minishell *ms, t_li_line *li_env, char **env, t_li_line *li, t_err *err)
{
	if (ms->nb_arg == 0)
		return (0);
	if (ft_strcmp(ms->arg[0], "echo") == 0)
	{
		echo(ms, err);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "pwd") == 0)
	{
		pwd(err);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "export") == 0)
	{
		export(ms, li_env, env, err);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "env") == 0)
	{
		envi(env, err);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "cd") == 0)
	{
		if (change_directory(ms, li_env, err) == -1)
			return (-1);
		return (1);
	}
	if (ft_strcmp(ms->arg[0], "exit") == 0)
		exit_minishell(1, ms, li_env, li, env, err);
	if (ft_strcmp(ms->arg[0], "unset") == 0)
	{
		unset(li_env, ms, err);
		return (1);
	}
	return (0);
}

static int	execut(t_minishell *ms, t_pipex *pipex, int i, t_li_line *li_env, t_li_line *li, t_err *err)
{
	char	**env;
	int		return_value;

	close(pipex->fd[0]);
	if (ms->nb_in > 0)
	{
		return_value = redir_in(ms, pipex, err);
		if (return_value != 0)
			return (ft_free_ms(ms), return_value);
	}
	else if (pipex->tmp_pipe != -1)
	{
		if (dup2(pipex->tmp_pipe, 0) == -1)
			return (-1);
		close(pipex->tmp_pipe);
	}
	if (ms->nb_out > 0)
	{
		return_value = redir_out(ms, pipex, err);
		if (return_value != 0)
			return (ft_free_ms(ms), return_value);
	}
	else if (i < pipex->nb_pipe)
	{
		if (dup2(pipex->fd[1], 1) == -1)
			return (-1);
		close(pipex->fd[1]);
	}
	env = liste_env_to_tab(li_env);
	if (check_builtins(ms, li_env, env, li, err) == 1)
		return (free(env), 0);
	if (ms->arg[0] != NULL)
	{
		if (cmd_path(ms->arg[0], env, err) == NULL)
		{
			ft_printf("FUK OFF\n");
			err->err = 127;
			return (ft_free_ms(ms), free(env), -1);
		}
		execve(cmd_path(ms->arg[0], env, err), ms->arg, env);
		free(env);
	}
	exit(EXIT_FAILURE);
}

static int	redir_in(t_minishell *ms, t_pipex *pipex, t_err *err)
{
	int	i;

	i = 0;
	dprintf(2, "NOM DE FICHIER OUVERTURE : %s\n", ms->in[i].str);
	while (ms->in[i].str && ms->in[i].type == 2)
	{
		pipex->infile = open(ms->in[i].str, O_RDONLY);
		if (pipex->infile == -1)
		{
			err->err = 126;
			return (126);
		}
		i++;
	}
	if (dup2(pipex->infile, 0) == -1)
		return (-1);
	close(pipex->infile);
	return (0);
}

static int	redir_out(t_minishell *ms, t_pipex *pipex, t_err *err)
{
	int	i;

	i = 0;
	while (ms->out[i].str)
	{
		if (ms->out[i].type == 6)
		{
			pipex->outfile = open(ms->out[i].str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (pipex->outfile == -1)
			{
				err->err = 126;
				return (126);
			}
		}
		else
		{
			pipex->outfile = open(ms->out[i].str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (pipex->outfile == -1)
			{
				err->err = 126;
				return (126);
			}			
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
