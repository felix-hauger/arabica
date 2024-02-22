CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD 
NAME = arabica
SRC = arabica.c TestOperation.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re