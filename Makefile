NAME = philo

HEADER = includes/philo.h

LIST = philo.c srcs/utils.c srcs/monitoring.c srcs/necessary_funcs.c srcs/print_status.c srcs/process_philo.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(LIST:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

%.o : %.c $(HEADER)
	gcc $(FLAGS) -I $(HEADER) -c $< -o $@

${NAME} : $(OBJ) $(HEADER)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all