/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:21:14 by mbogey            #+#    #+#             */
/*   Updated: 2024/01/05 14:58:59 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_buffer(size_t *nb, char *buf, char **tmp);
char	*get_line(int fd, char *buf, size_t *nb, ssize_t *size);
void	clear_buf(char *buf, size_t nb);
char	*ft_free(char *tmp, char *buf);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {'\0'};
	char		*line;
	size_t		nb;
	ssize_t		size;

	nb = 0;
	size = 0;
	line = get_line(fd, buf, &nb, &size);
	clear_buf(buf, nb);
	return (line);
}

int	check_buffer(size_t *nb, char *buf, char **tmp)
{
	if (buf[0] != '\0')
	{
		*tmp = ft_strdup_gnl(buf, nb);
		if (*tmp == 0)
			return (0);
	}
	return (1);
}

char	*get_line(int fd, char *buf, size_t *nb, ssize_t *size)
{
	char	*tmp;

	tmp = NULL;
	if (check_buffer(nb, buf, &tmp) == 0)
		return (NULL);
	if (*nb != 0)
		return (tmp);
	*size = read(fd, buf, BUFFER_SIZE);
	if (*size < 0)
		return (ft_free(tmp, buf));
	while (*size > 0)
	{
		buf[*size] = '\0';
		tmp = ft_strjoin_gnl(tmp, buf, nb);
		if (tmp == NULL)
			return (NULL);
		if (*nb != 0)
			break ;
		*size = read(fd, buf, BUFFER_SIZE);
		if (*size < 0)
			return (ft_free(tmp, buf));
	}
	return (tmp);
}

void	clear_buf(char *buf, size_t nb)
{
	if (nb != 0)
		ft_memmove_gnl(buf, buf + nb, ft_strlen_n(buf + nb, '\0'));
	else
		buf[0] = 0;
}

char	*ft_free(char *tmp, char *buf)
{
	if (tmp != NULL)
		free(tmp);
	buf[0] = 0;
	return (NULL);
}
