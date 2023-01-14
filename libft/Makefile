CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=libft.a
SRC=ft_atoi.c ft_calloc.c ft_isdigit.c ft_atoi.c ft_strncmp.c ft_strlen.c ft_memset.c ft_bzero.c ft_split.c ft_strlcpy.c ft_strlcat.c ft_strjoin.c
OBJ=$(SRC:.c=.o)

.PHONY:clean fclean re bonus

all:$(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
	ar -cr $(NAME) $@

$(NAME):$(OBJ)

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re:fclean all
