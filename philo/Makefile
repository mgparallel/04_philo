CC = -gcc
CFLAGS = -Wall -Werror -Wextra
LIBS = -lpthread #check
SANITIZE = -fsanitize=address
RM = rm -rf
NAME = philo

SRC = $(wildcard *.c)

SRC_BONUS = bonus/*.c

OBJS = $(SRC:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS) Makefile $(HEADER)
			$(CC) $(CFLAGS) -o $(NAME) $(LIBS) $(OBJS) $(SANITIZE)

bonus: .bonus

.bonus: $(OBJS_BONUS) Makefile $(HEADER)
	$(AR) $(NAME) $(OBJS_BONUS)
	touch .bonus

%.o: %.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

PHONY: all clean fclean re