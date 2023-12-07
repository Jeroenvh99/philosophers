NAME = philo
CFLAGS = -Wall -Werror -Wextra
OBJS = ${SRCS:.c=.o}
SRCS = main.c \
	setup.c \
	utils.c \
	philo.c \
	monitoring.c

all: $(NAME)

$(NAME): $(SRCS)
	cc $(SRCS) $(CFLAGS) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re