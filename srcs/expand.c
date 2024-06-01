#include "mini_shell.h"

int	is_alnum_or8(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

char	*get_env(char *s, t_li_line *env, size_t i)
{
	size_t	j;

	while (env->next != NULL)
	{
		j = 0;
		if (env->token.str[0] == s[i + 1])
		{
			while (env->token.str[j] == s[i + 1 + j])
			{
				if (env->token.str[j + 1] == '='/* && is_alnum_or8(s[i + 2 + j]) == 0*/)
				{
					return (env->token.str + j + 2);
				}
				j++;
			}
		}
		env = env->next;
	}
	return (NULL);
}

size_t	ft_strlen_alnum(char *s)
{
	size_t	i;

	i = 1;
	while (s[i] && (is_alnum_or8(s[i]) == 1 || s[i] != '$'))
		i++;
	return (i);
}

// void	fill_new_s(char **new_s, char *s, char *var)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	k;
// 	int		count;

// 	count = 0;
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$' && count == 0)
// 		{
// 			count = 1;
// 			while (var[k])
// 			{
// 				(*new_s)[j] = var[k];
// 				k++;
// 				j++;
// 			}
// 			i++;
// 			while (s[i] != '\0' && is_alnum_or8(s[i]) == 1)
// 				i++;
// 		}
// 		(*new_s)[j] = s[i];
// 		i++;
// 		j++;
// 	}
// 	(*new_s)[j] = '\0';
// 	printf("j = %zu\n",j);
// }

char	*move_str(size_t size, char *s)
{
	char	*new_s;
	size_t	i;
	size_t	j;
	int		count;

	count = 0;
	i = 0;
	j = 0;
	new_s = malloc(sizeof(char) * (size + 1));
	if (new_s == NULL)
		return (NULL);
	new_s[size] = '\0';
	printf("size = %zu\n", size);
	while (s[i])
	{
		if (s[i] == '$' && count == 0)
		{
			count = 1;
			i++;
			while (s[i] != '\0' && is_alnum_or8(s[i]) == 1)
				i++;
		}
		if (s[i] != '\0')
		{
			new_s[j] = s[i];
			i++;
			j++;
		}
		else
			new_s[j] = '\0';
	}
//	new_s[j] = '\0';
	return (new_s);
}
char	*fill_new_s(size_t size, char *s, char *var)
{
	char	*new_s;
	size_t	i;
	size_t	j;
	size_t	k;
	int		count;

	count = 0;
	i = 0;
	j = 0;
	k = 0;
	new_s = malloc(sizeof(char) * (size + 1));
	while (s[i] != '\0')
	{
		if (s[i] == '$' && count == 0)
		{
			count = 1;
			while (var[k])
			{
				new_s[j] = var[k];
				k++;
				j++;
			}
			i++;
			while (s[i] != '\0' && is_alnum_or8(s[i]) == 1)
				i++;
		}
		if (s[i] != '\0')
		{
			new_s[j] = s[i];
			i++;
			j++;
		}
		else
			new_s[j] = '\0';
	}
	new_s[j] = '\0';
	return (new_s);
}

char	*get_return_value(char *s, t_err *err)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*itoa_err;
	char	*new_s;

	i = 0;
	j = 0;
	k = 0;
	itoa_err = ft_itoa(err->err);
	printf("\nitoa char = %s\n", itoa_err);
	new_s = malloc(sizeof(char) * (ft_strlen(itoa_err) + ft_strlen(s)
			- 2 + 1));
	new_s[ft_strlen(itoa_err) + ft_strlen(s)
			- 2] = '\0';
	if (new_s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			while (itoa_err[k])
			{
				new_s[j] = itoa_err[k];
				j++;
				k++;
			}
			i += 2;
		}
		if (s[i])
		{
			new_s[j] = s[i];
			i++;
			j++;
		}
		else
			new_s[j] = '\0';
	}
	new_s[j] = '\0';
//	free(itoa_err);
//	free(s);
	return(new_s);
}

char	*str_expand(char *s, t_li_line *env, size_t i, t_err *err)
{
	char	*var;
	char	*new_s;
	size_t	size;
//si $?
//si $USER <-ex qqch qui existe dans env
//si $popo <-""""""""""" n'existe pas
	var = get_env(s, env, i);
	printf("var = %s\n", s);
	if (s[i + 1] == '?')
		new_s = get_return_value(s, err);
	else if (var != NULL)
	{
		//printf("size = %zu %zu %zu\n",ft_strlen(s), ft_strlen(var) , ft_strlen_alnum(s + i));
		//new_s = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(var) - ft_strlen_alnum(s + i) + 1));
		//if (new_s == NULL)
		//	return (NULL); // voir protection a faire
		size = ft_strlen(s) + ft_strlen(var) - ft_strlen_alnum(s + i) + 1;
		//fill_new_s(&new_s, s, var);
		new_s = fill_new_s(size, s, var);
	}
	else
	{
		size = ft_strlen(s) - ft_strlen_alnum(s + i) + 1;
		new_s = move_str(size , s);
	}
	free(s);
	return (new_s);
}

void	expand(t_li_line *li, t_li_line *env, t_err *err)
{
	size_t	i;
	(void)	env;
	ft_printf("return value avant expand %d\n", err->err);
	printf("\033[0;32m-------------- expand ---------------\033[0m\n");
	while (li->next)
	{
		i = 0;
		while (li->token.str[i])
		{
			if (li->token.str[i] == '\'')
			{
				i++;
				while (li->token.str[i] != '\'')
					i++;
			}
			if (li->token.str[i] == '$')
			{
				li->token.str = str_expand(li->token.str, env, i, err);
				printf("%s", li->token.str);
				i = -1;
			}
			i++;
		}
		printf("\n");
		li = li->next;
	}
	printf("\033[0;32m-------------- END expand ------------\033[0m\n");
}