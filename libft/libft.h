/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbogey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:30:17 by mbogey            #+#    #+#             */
/*   Updated: 2023/11/22 11:00:45 by mbogey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int					ft_atoi(const char *c);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *memoryBlock, int n, size_t size);
int					ft_memcmp(const void *pointer1,
						const void *pointer2, size_t size);
void				*ft_memcpy(void *dest, const void *s, size_t size);
void				*ft_memmove(void *dest, const void *s, size_t size);
void				*ft_memset(void *p, int value, size_t count);
char				*ft_strchr(const char *s, int n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t n);
size_t				ft_strlen(const char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *first, const char *second,
						size_t len);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *str, int n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_calloc(size_t elementCount, size_t elementSize);
char				*ft_strdup(const char *source);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

# define HEXUP "0123456789ABCDEF"
# define HEXLOW "0123456789abcdef"
# define DEC "0123456789"

int					ft_printf(const char *format, ...);
int					ft_putchar(char c, size_t *count);
int					ft_putnbr(int n, size_t *count);
int					ft_putstr(char *s, size_t *count);
int					ft_putunsign(unsigned int nb, size_t *count);
int					ft_putnbr_base(unsigned int nb, char *base, size_t *count);
unsigned int		ft_strlen_print(char *s);
int					ft_print_p(unsigned long i, size_t *count);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char				*get_next_line(int fd);
size_t				ft_strlen_n(char *s, char c);
char				*ft_strdup_gnl(char *s, size_t *nb);
char				*ft_strjoin_gnl(char *s1, char *s2, size_t *nb);
void				*ft_memmove_gnl(void *dest, const void *s, ssize_t size);

#endif
