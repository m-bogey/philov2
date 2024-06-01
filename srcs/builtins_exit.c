#include "mini_shell.h"

void	exit_minishell(int status, t_minishell *ms, t_li_line *li_env, t_li_line *li, char **env, t_err *err)
{
	ft_free_li(li);
	ft_free_li(li_env);
	ft_free_ms(ms);
	free(env);
	if (ms->heredoc != NULL)
		free(ms->heredoc);
	err->err = status;
	ft_printf("exit\n");
	exit(status);
}
