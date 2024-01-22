NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_split.c ft_help_split.c ft_pipex.c utils.c pipex.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re