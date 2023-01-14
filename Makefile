CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=pipex
SRC=pipex.c help_func.c get_path.c
OBJ=$(SRC:.c=.o)
SRC_O=BONUS/help_funcs.c BONUS/help_funcs1.c BONUS/help_funcs2.c BONUS/pipex_bonus.c gnl/get_next_line.c gnl/get_next_line_utils.c
BONUS_O=$(SRC_O:.c=.o)

all:$(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJ)
	make -C libft/
	$(CC) $(OBJ) libft/libft.a -o $(NAME)

bonus:$(BONUS_O)
	make -C libft/
	$(CC) $(BONUS_O) libft/libft.a -o pipex

clean:
	make clean -C libft/
	rm -f $(OBJ) $(BONUS_O)

fclean:clean
	make fclean -C libft
	rm -f $(NAME)

re:fclean all
