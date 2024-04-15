#include "mini_shell.h"

void    init_struct(t_pipex *pipex)
{
	pipex->tmp_pipe = -1;
	pipex->nb_pipe = 0;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pid = -1;
	//pipex->fd[0] = -1;
	//pipex->fd[1] = -1;
}