#include "mini_shell.h"

//------- type : 0 1 = arg   2 = <   3 = >   4 = <<   5 = |   6 = >>
static int	check_delim(char *delim, char c)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (' ' == c || '\t' == c)
			return (1);
		if ('<' == c)
			return (2);
		if ('>' == c)
			return (3);
		if ('|' == c)
			return (5);
		i++;
	}
	return (0);
}

t_token	ft_strtok(char *str, char *delim)
{
	t_token		token;
	int			i;
	int			begin;
	static char	*ptr_word;
	int			type;

	token.str = NULL;
	token.type = 0;
	i = 0;
	begin = 0;
	if (str == NULL)
	{
		if (ptr_word != NULL)
			str = ptr_word;
		else
			return (token);
	}
	while (check_delim(delim, str[i]) == 1)
		i++;
	begin = i;
	type = check_delim(delim, str[i]);
	while (str[i] && type == 0)
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
		}
		i++;
		type = check_delim(delim, str[i]);
	}
	if (str[i] != '\0')
	{
		str[i] = '\0';
		ptr_word = str + i + 1;
	}
	else
		ptr_word = NULL;
	token.str = ft_strdup(str + begin); // voir si garder strdup
	token.type = type;
	return (token);
}