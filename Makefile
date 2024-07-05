NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread -g3

SRC = main.c parse.c utils.c time.c monitor.c routine.c

OSRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
	@echo "Compiling ..."
	@$(CC) $(CFLAGS) $(OSRC) -o $(NAME)

%.o: %.c philo.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning ..."
	@rm -rf $(OSRC)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY = clean
