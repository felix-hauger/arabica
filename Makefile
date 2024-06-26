CC = gcc
CFLAGS = -Wall -Wextra -Werror -I -MMD 
NAME = arabica
SRC_DIR = src/
BUILD_DIR = build/
SRC = main.c analyze.c compile.c utils.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJ = $(SRCS:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(shell mkdir -p $(BUILD_DIR))
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re