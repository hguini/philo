NAME = philo

SRC = main.c ft_atoi.c

CC = gcc -Wall -Werror -Wextra

HEAD = includes/philo.h

all:$(NAME)

$(NAME):$(SRC) 
	$(CC) $(SRC)
	mv a.out ./philo

clean:
	rm -rf $(NAME)

fclean: clean
		rm *.gch

norm:
	norminette $(SRC)
	norminette 

re: fclean all

PHONY: all clean fclean re