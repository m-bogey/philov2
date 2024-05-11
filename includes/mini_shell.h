#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <readline/readline.h> // readline
# include <readline/history.h> // readline history
# include "libft.h"
# include <stdlib.h> // malloc free
# include <unistd.h>
# include <fcntl.h> // open
# include "path.h"

# define ALNUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

typedef struct s_out
{
	char	*str;
	int		type;
}				t_out;

typedef struct s_minishell
{
	char	**arg;
	t_out	*in;
	t_out	*out;
	int		nb_arg;
	int		nb_in;
	int		nb_out;
	char	*heredoc;
	char	*temp_name;
	int		temp_fd;
	struct s_minishell	*next;
}				t_minishell;

t_minishell	*new_list(void);
void		add_back(t_minishell *ms);
void		ft_free_ms(t_minishell *ms);


//-----------parsing---------

typedef struct s_token
{
	char		*str;
	int			type;
}				t_token;

typedef struct s_li_line
{
	t_token				token;
	struct s_li_line	*next;
}				t_li_line;


t_token		ft_strtok(char *str, char *delim); // voir si utilise
t_li_line	*parsing(char *line);
t_li_line	*new_list_pars(t_token *tok);
void		add_back_pars(t_li_line *li, t_token *tok);
void		print_list_pars(t_li_line *li);      // a suprimer
void		ft_free_li(t_li_line *li);

//----------- create env ----------

t_li_line	*liste_env(char **envp);
size_t		count_liste(t_li_line *list);
char		**liste_env_to_tab(t_li_line *li_env);

//----------- execut ---------------

typedef struct s_pipex
{
	int		fd[2];
	int 	tmp_pipe;
	int		nb_pipe;
	pid_t	pid;
	int		infile;
	int		outfile;
}				t_pipex;

int	pre_execut(t_minishell *ms, t_pipex *pipex, t_li_line *li_env);

//----------- init -----------------

void    init_struct(t_pipex *pipex);

//----------- heredoc --------------
int		heredoc(t_minishell *ms);
int		temp_file(t_minishell *ms);

//----------- expand ---------------
void	expand(t_li_line *li, t_li_line *env);

//----------- builtins -------------
void	echo(t_minishell *ms);
void	pwd(void); // voir si return necessaire pour getcwd
void	export(t_minishell *ms, t_li_line *li_env, char **env);
void	envi(char **env);
int		change_directory(t_minishell *ms, t_li_line *li_env);
void	exit_minishell(int status);
void	unset(t_li_line *li_env, t_minishell *ms);

//----------- remove quote --------
int	remove_quote(t_li_line *li);

#endif