NAME = minishell 
CC = CC

FLAGS = -Wall -Werror -Wextra

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = main.c\
			   list_tools.c\
			   ft_split.c\
			   ft_strcmp.c\
			   ft_strchr.c\
GREEN			=	"\033[1;32m"
PURPLE			=	"\x1b[35m"
RED				=  "\033[0;31m"

SRC = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJ = ${SRC:.c=.o}

%.o: %.c ./includes/minishell.h
	$(CC) $(FLAGS) -o $@ -c $<

all: ${NAME}

${NAME}: ${OBJ}
	$(CC) $(FLAGS) $(OBJ) -o ${NAME}
	@echo ${PURPLE}"$(NAME): Compiling"


clean:
	rm -rf $(OBJ) ${OBJ_BONUS}

fclean: clean
	rm -rf $(NAME)
	@echo ${GREEN}"$(NAME) : nadafa mina l iman ..."

re: fclean all
