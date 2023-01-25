NAME = philo

SRC_DIR = src/
OBJ_DIR = .objs

SRCS_FILES = philo.c init.c check_args.c logs.c utils.c threading.c routine.c moves.c

SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
LFLAGS = -pthread -fsanitize=thread
RM = rm -rf


all: $(NAME)
#@echo "BOOM 💥💥💥💥💥 $(NAME) Compiled! 💯 $(DEFAULT)"

$(NAME): $(OBJS)
		@$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(NAME)
#@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

bonus:
	

clean:
		@$(RM) $(OBJS)
		@echo "$(YELLOW)Object files deleted!$(DEFAULT)💯"

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PONY: all clean fclean re

git:
	@git add .
	@git commit -m "$(message)"
	@git push
	@echo "\n$(GREEN)$(message) Committed!$(DEFAULT)💯"

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
message = "Commit Message By Default On $(shell date "+%d %B %T")"
