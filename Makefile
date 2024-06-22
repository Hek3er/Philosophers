NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = main.c parse.c utils.c time.c

OSRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
	@echo "Compiling ..."
	@$(CC) $(CFLAGS) $(OSRC) -o $(NAME)

%.o: %.c philo.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning ..."
	@rm -rf $(OSRC)

fclean: clean
	@rm -rf $(NAME)

.PHONY = clean