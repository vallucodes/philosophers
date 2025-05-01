NAME		= philo
CC			= cc
CFLAGS		= -g -Wextra -Wall #-Werror

OBJ_DIR		= obj/
SRC_DIR		= src/

HEADERS		= -I ./inc
PHILOH		= ./inc/philo.h

SRC			=	main.c \
				exit.c \
				handles.c \
				init.c \
				parsing.c \
				routine_observer.c \
				routine_philo.c \
				utils.c

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
