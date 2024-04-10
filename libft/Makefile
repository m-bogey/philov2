NAME = libft.a

SRC = \
	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c \
	ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_print_p.c ft_printf.c ft_putchar.c ft_putnbr_base.c ft_putnbr.c \
	ft_putstr.c ft_putunsign.c ft_strlen_print.c \
	get_next_line.c get_next_line_utils.c

SRC_B = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)


%.o : %.c libft.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):$(OBJ)
	$(AR) rcs $(NAME) $(OBJ)

.PHONY : all clean fclean re

clean :
	$(RM) $(OBJ) $(OBJ_B)

fclean : clean
	$(RM) $(NAME)

re:	fclean
	$(MAKE) all

.PHONY : bonus

bonus : 
	$(MAKE) SRC="$(SRC) $(SRC_B)"
