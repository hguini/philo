#==================================>COLORS<====================================#

_RED		=	\e[31m
_YELLOW		=	\e[33m
_GREEN		=	\e[32m
_END		=	\e[0m

#==================================>FILES<=====================================#

SRC			=	main.c \

SRCS		=	$(SRC)

#===============================>COMPILATIONS<=================================#

GCC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

#===================================>DELETE<===================================#

RM			=	rm -rf

#=================================>DIRECTORIES<================================#

DIR_HEAD	=	./includes

LIB_HEAD	=	./libft/Libft.a

#===============================>COMPILED_SOURCES<=============================#

OBJS		=	${SRCS:%.c=%.o}

NAME		=	philo

#================================>COMPILED_RULES<==============================#

all:			${NAME}

${NAME}:		${OBJS}
				@${MAKE} -C ./libft
				@${GCC} ${CFLAG} -o ${NAME} ${OBJS} ${LIB_HEAD}
				@printf "\033[2K\r${_GREEN} Philosophers create: '${NAME}'. ${_END}✅\n"

#===========================>COMPILED_SOURCES_RULES<===========================#

%.o:			%.c
				@$(GCC) $(CFLAGS) -I $(DIR_HEAD) -c $< -o $@
				@printf "\033[2K\r$(_YELLOW) Compiling $< $(_END)⌛"

#===================================>NORM_RULES<===============================#

norm:
				@norminette .			

#====================================>CLEAN_RULES<=============================#

clean:
			@make clean -C ./libft
			@rm -f ${OBJS}
			@printf "\033[2K\r${_RED} '".o"' has been deleted. ${_END}🗑️\n"

fclean:		clean
			@make fclean -C ./libft
			@rm -f ${NAME}
			@printf "\033[2K\r${_RED} '"${NAME}"' has been deleted. ${_END}🗑️\n"

re:			fclean all

.PHONY: all clean fclean re