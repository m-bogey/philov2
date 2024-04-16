#ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include <stdio.h>
#include <readline/readline.h> // readline
#include <readline/history.h> // readline history
#include "libft.h"
#include <stdlib.h> // malloc free
#include <unistd.h>
#include <fcntl.h> // open
#include "path.h"

typedef	struct s_out
{
	char	*str;
	int		type; // 0 pour out >    ou      1 pour append >>
}				t_out;

typedef struct  s_minishell
{
        char    **arg;
        char    **in;
        t_out	*out;
		int		nb_in;
		int		nb_out;
		struct	s_minishell *next;
}   t_minishell;

typedef	enum
{
	false,
	true
}bool_li;

t_minishell	*new_list();
/*bool_li	is_empty_list(t_li *li);
int		list_length(t_li *li);
void	print_list(t_li *li);*/
void	add_back(t_minishell *ms);


//-----------parsing---------

typedef struct	s_token
{
	char		*str;
	int			type;
}				t_token;

typedef	struct	s_li_line
{
	t_token		token;
	struct s_li_line	*next;
}				t_li_line;


t_token    ft_strtok(char *str, char *delim); // voir si utilise
t_li_line		*parsing(char *line);
t_li_line	*new_list_pars(t_token *tok);
void	add_back_pars(t_li_line *li, t_token *tok);
void	print_list_pars(t_li_line *li);

//----------- execut ---------------

typedef struct	s_pipex
{
				int		fd[2];
				int 	tmp_pipe;
				int		nb_pipe;
				pid_t	pid;
				int		infile;
				int		outfile;
}				t_pipex;

int		pre_execut(t_minishell *ms, t_pipex *pipex, char **envp);

//----------- init -----------------

void    init_struct(t_pipex *pipex);

#endif