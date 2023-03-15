NAME = philo
CC = cc
ARQH = -c -Iinclude
CFLAGS = -Wall -Werror -Wextra -lpthread $(INCLUDE)
SRC = check_args.c check_stop.c init_var.c\
	  main.c mutex_list.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
