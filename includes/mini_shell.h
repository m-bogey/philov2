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
        int     infile;
        int     outfile;
        char    **arg;
        char    **in;
        t_out	**out;
		struct	s_minishell *next;

		int		nb_elem;
		pid_t	pid;
		int		fd[2];
        int     tmp_pipe;
		int		nb_pipe;
}   t_minishell;


typedef	struct	s_li
{
	t_minishell	*ms;
	struct s_li	*next;
}				t_li;

typedef	enum
{
	false,
	true
}bool_li;

t_li	*new_list(t_minishell *ms);
bool_li	is_empty_list(t_li *li);
int		list_length(t_li *li);
void	print_list(t_li *li);
void	add_back(t_li *li, t_minishell *ms);


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

#endif