NAME		= philo
CC			= cc
CFLAGS		= -Wextra -Wall -Werror

OBJ_DIR		= obj/
SRC_DIR		= src/

HEADERS		= -I ./inc
PHILOH		= ./inc/philo.h

SRC			=	main.c \
				cleanup.c \
				init.c \
				parsing.c \
				print_error.c \
				routine_observer.c \
				routine_philo_actions.c \
				routine_philo.c \
				routine_utils.c \
				thread_mutex_handles.c \
				utils_libft.c

OBJS		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(PHILOH)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(PHILOH)
	$(CC) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
