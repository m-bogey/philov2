#include "mini_shell.h"

static int	check_end_quote(char *line);

int	pre_parsing(char *line)
{
	if (check_end_quote(line) == -1)
	{
		ft_printf("minishell: syntax error need end of quote\n");
		return (-1);
	}
	return (0);
}

static int	check_end_quote(char *line)
{
	size_t	i;
	int		quote;
	int		single_q;
	int		double_q;

	i = 0;
	quote = 1;
	single_q = 1;
	double_q = 1;
	while (line[i])
	{
		if (line[i] == '\'' && double_q == 1)
		{
			single_q *= -1;
			quote *= -1;
		}
		if (line[i] == '\"')
		{
			double_q *= -1;
			quote *= -1;
		}
		i++;
	}
	return (quote);
}