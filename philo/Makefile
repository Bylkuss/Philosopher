NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
LFLAGS = -pthread -fsanitize=thread
RM = rm -rf

SRCDIR = src/
OBJDIR = .bin/

SRCS_FILES = src/philo.c src/init.c src/check_args.c src/logs.c src/utils.c src/threading.c src/routine.c src/moves.c
SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "$(GREEN)Compiled!$(DEFAULT)💯"

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJDIR)
	@echo "$(YELLOW)Object files deleted!$(DEFAULT)💯"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PONY: all clean fclean re

commit:
	@git add .
	@git commit -m "$m $(COMMIT)"
	@git push origin "$b"
	@echo "\n$(GREEN)$(message) Committed!$(DEFAULT)💯"

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
COMMIT = $(shell date "+%d %B %T")
