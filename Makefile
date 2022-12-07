
NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -rf

SRCS = srcs/main.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

 $(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)
re:
	all fclean
.PHONY:
	all clean fclean re