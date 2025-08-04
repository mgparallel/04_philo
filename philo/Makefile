CC = -gcc
CFLAGS = -Wall -Werror -Wextra -g
LIBS = -lpthread
SANITIZE = -fsanitize=thread
RM = rm -rf
NAME = philo

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS) Makefile $(HEADER)
			$(CC) $(CFLAGS) -o $(NAME) $(LIBS) $(OBJS) $(SANITIZE)

%.o: %.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re