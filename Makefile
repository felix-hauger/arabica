CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD 
NAME = arabica
SRC_DIR = src/
BUILD_DIR = build/
SRC = arabica.c TestOperation.c getName.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(SRCS:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re