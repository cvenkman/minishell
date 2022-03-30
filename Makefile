NAME	=	minishell

PARSER	=	$(addprefix parser/, parser.c string.c read_env.c parse_redirect.c string_builder.c heredoc.c \
			parser2.c parser3.c parse_red.c)
BUILTIN	=	$(addprefix builtins_and_cmd/, env.c pwd.c run_cmd.c distribution.c cd.c signals.c \
			command.c pipe.c echo.c export_and_unset/export.c export_and_unset/print_export.c exit.c \
			export_and_unset/export_utils.c export_and_unset/unset.c export_and_unset/check_valid.c)

SRCS	=	${PARSER} ${BUILTIN} main.c\
			util/errors.c	util/utils.c	util/strarr_utils.c\
			util/cvenkman/cvenkman.c		util/cvenkman/change_shell_lvl.c

OBJS		=	$(SRCS:.c=.o)

FLAGS		=	-Wall -Wextra -Werror -I ~/.brew/opt/readline/include
LIBFTMAKE 	=	$(MAKE) -C libft/
CC			=	gcc
RDL_MAC		=	-lreadline -L ~/.brew/opt/readline/lib
%.o: %.c
	cd $(@D) && $(CC) $(FLAGS) -c $(<F)

all: libft/libft.a $(NAME)

libft/libft.a:
	@$(LIBFTMAKE)

$(NAME): $(OBJS) minishell.h
	$(CC) -o $@ $(OBJS) $(RDL_MAC) libft/libft.a -L 

clean:
	rm -f  $(OBJS)
	$(LIBFTMAKE) clean

debug:
	$(CC) -g -o $(NAME) $(SRCS) libft/*.c -lreadline -I

fclean:
	rm -f $(NAME) $(OBJS)
	$(LIBFTMAKE) fclean

re: fclean all

.PHONY:	all clean fclean re libft/libft.a debug