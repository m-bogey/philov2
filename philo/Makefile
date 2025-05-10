NAME = philo

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDES)  #-fsanitize=thread

SRC_DIR = srcs

INCLUDES = includes

BUILD_DIR = .build

SRC_FILES = main.c \
			parsing.c \
			init.c \
			start_simulation.c \
			getime.c \
			print_mutex.c \
			routine.c \
			usleep_with_check_die.c \
			check_end_simulation.c \
			wait_for_begin.c \
			clean.c \
			safe_init_mutex.c \
			ft_atol.c

SRC = $(addprefix $(SRC_DIR)/, SRC_FILES)

OBJ = $(addprefix $(BUILD_DIR)/, $(SRC_FILES:.c=.o))

DEPS = $(OBJ:.o=.d)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) -o $(NAME) $(OBJ)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJ) $(BUILD_DIR)

.PHONY: all clean fclean re