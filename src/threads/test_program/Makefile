CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -pthread
SRC		:= threads.c
NAME	:= thr_test
OBJ		:= $(SRC:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all