#include "mini_shell.h"

void	config_liste(t_li_line *li);

t_li_line	*new_list_pars(t_token *tok);
void	add_back_pars(t_li_line *li, t_token *tok);
void	print_list_pars(t_li_line *li);

size_t	count_meta(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '|')
			count++;
		if (line[i] == '<')
		{
			count++;
			if (line[i + 1] == '<')
				i++;
		}
		if (line[i] == '>')
		{
			count++;
			if (line[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (count);
}

char	*new_line_with_space(char *line)
{
	size_t	size_line;
	char	*new_line;
	size_t	count_m;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	size_line = ft_strlen(line);
	count_m = count_meta(line);
	new_line = malloc(sizeof(char) * (size_line + (count_m * 2) + 1));
	if (new_line == NULL)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			new_line[j] = ' ';
			new_line[j + 1] = line[i];
			if (line[i] == '<' && line[i + 1] == '<')
			{
				i++;
				j++;
				new_line[j + 1] = line[i];
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				i++;
				j++;
				new_line[j + 1] = line[i];
			}
			new_line[j + 2] = ' ';
			j += 2;
		}
		else
			new_line[j] = line[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	//free(line);
	return (new_line);
}

// void	dup_str_in_li(t_li_line *li)
// {
// 	while (li->next)
// 	{
// 		li->token.str = ft_strdup(li->token.str);
// 		li = li->next;
// 	}
// }

t_li_line	*parsing(char *line)
{
	t_li_line	*li;
	t_token		token;

	line = new_line_with_space(line);
	token = ft_strtok(line, " \t<>|");
	li = new_list_pars(&token);
	while (token.str)
	{
		token = ft_strtok(NULL, " \t<>|");
		add_back_pars(li, &token);
	}
	config_liste(li);
	free(line);
	//dup_str_in_li(li);
	return (li);
}

void	config_liste(t_li_line *li)
{
	t_li_line	*tmp;

	tmp = li;
	print_list_pars(li);
	while (li->next != NULL)
	{
		if (li->token.type == 5)
			if (li->next->token.type == 2 || li->next->token.type == 3 || li->next->token.type == 4 || li->next->token.type == 6 || li->next->token.type == 5)
				ft_printf("bash: syntax error near unexpected token `|'\n");
		if (li->token.type == 2)
		{
			if (li->next->token.type == 2)
			{
				if (li->next->next->token.str[0] == '\0')
					ft_printf("bash: syntax error near unexpected token `<<'\n");
				li = li->next;
				li->next->token.type = 4;
			}
			else
			{
				if (access(li->next->next->token.str, W_OK) == -1 || li->next->next->token.str[0] == '\0')
					ft_printf("bash: syntax error near unexpected token `<'\n");
				li->next->token.type = 2;
			}
			li = li->next;
		}
		if (li->token.type == 3)
		{
			if (li->next->token.type == 3)
			{
				if (li->next->next->token.str[0] == '\0')
					ft_printf("bash: syntax error near unexpected token `>>'\n");
				li = li->next;
				li->next->token.type = 6;
			}
			else
			{
				if (li->next->token.str[0] == '\0')
					ft_printf("bash: syntax error near unexpected token `>'\n");
				li->next->token.type = 3;
			}
			li = li->next;
		}
		li = li->next;
	}
	printf("\n\033[0;31m--------------------------\033[0m\n");
	print_list_pars(tmp);
}
