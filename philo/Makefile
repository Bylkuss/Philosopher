NAME = philo

SRCS_PATH = src/

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g #-lpthread
# CFLAGS = -Wall -Werror -Wextra #-lpthread
RM = rm -rf

SRCS_FILES = philo.c init.c check_args.c logs.c utils.c threading.c routine.c moves.c
# SRCS_FILES = logs.c main.c utils.c routine.c philo.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJS_DIR = bin/

OBJS = $(subst $(SRCS_PATH), $(OBJS_DIR), $(SRCS:.c=.o))
# $(SRCS:.c=.o)


$(OBJS_DIR)%.o :	$(SRCS_PATH)%.c
			@mkdir -p $(OBJS_DIR)
			@$(CC) $(CFLAGS) -c $< -o $@


all: 	$(NAME)
	@echo "$(GREEN)Your program compiled succefully!💥\n$(DEFAULT)"


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) created!$(DEFAULT)💯"
	
clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)💯"

fclean:	clean
	@$(RM) $(NAME) $(LIBFT)

commit:
	git add .
	git commit -m "$m $(COMMIT)"
	git push origin "$b"


re:		fclean all


.PHONY:	all clean libft fclean re


#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
COMMIT = $(shell date "+%d %B %T")