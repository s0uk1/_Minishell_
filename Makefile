NAME = minishell

YBA = minishell

CC = gcc

LDFLAGS = "-L/Users/ssabbaji/.brew/opt/readline/lib"
CPPFLAGS = "-I/Users/ssabbaji/.brew/opt/readline/include"

INCLUDESS        =  ${CPPFLAGS}

LIBRARIESS        = ${LDFLAGS} -lreadline

FLAGS = -Wall -Wextra -Werror

SRC = main.c ft_free.c ft_main.c ft_print_list.c\

ENV = ./env/ft_env.c ./env/ft_env_list.c\

PARSING = ./parsing/parsing.c ./parsing/parsing_utils.c \
		  ./parsing/ft_cmd_list.c ./parsing/ft_new_split.c \
		  ./delete_quotes/ft_delete_quotes.c ./delete_quotes/delete_quotes_utils.c \
		  ./parsing/exit_status.c ./parsing/parsing_utils2.c ./parsing/parsing_utils3.c\
		  ./parsing/parsing_utils4.c ./parsing/parsing_utils5.c \

EXPANDING = ./expanding/ft_expanding.c ./expanding/expanding_utils.c \
			./expanding/ft_len.c ./expanding/expanding_utils2.c \

LEXER = ./lexer/lexer.c ./lexer/lexer_utils.c \
		./lexer/ft_lexer_list.c \
		./lexer/ft_add_and.c ./lexer/ft_add_semi.c \
		./lexer/ft_add_parenth.c ./lexer/ft_add_word.c \
		./lexer/ft_add_pipe.c ./lexer/ft_add_redirection.c


SYNTAX = ./syntax/syntax_analyzer.c ./syntax/ft_pipe.c \
	 	 ./syntax/ft_redirection.c ./syntax/ft_quotes.c \

BUILTIN= ./builtin/unset.c \
		 ./builtin/export/export.c ./builtin/export/export_utils.c \
		 ./builtin/export/export_utils2.c ./builtin/export/export_utils3.c \
		 

UTILS= ./utils/ft_putstr_fd.c ./utils/ft_get_env.c ./utils/ft_itoa.c \
	   ./utils/ft_strcmp.c ./utils/ft_strlen.c ./utils/ft_calloc.c \
	   ./utils/ft_strchr.c ./utils/ft_trim.c \

EXECUT= ./execution/execution.c\
		./execution/my_mess/pipes.c\
		./execution/close_all.c \
		./execution/signals_handling.c\
		./execution/my_mess/counting_funcs.c ./execution/my_mess/custom_getenv.c\
		./execution/my_mess/my_exec.c ./execution/my_mess/my_export.c ./execution/my_mess/my_cd.c\
		./execution/my_mess/my_env.c ./execution/my_mess/my_echo.c  ./execution/my_mess/my_exit.c\
		

FILES = $(SRC) $(PARSING) $(LEXER) $(ENV) $(SYNTAX) $(BUILTIN) $(UTILS) $(EXPANDING) $(EXECUT)

OBJ = ${FILES:.c=.o}
 
%.o: %.c minishel.h
	$(CC) $(FLAGS) -c $< ${INCLUDESS} -o $@

all: ${NAME}

${NAME}: ${OBJ}
	$(CC) ${LIBRARIESS} $(OBJ) -o ${NAME}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ${NAME}

re: fclean all

