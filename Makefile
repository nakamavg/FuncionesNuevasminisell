NAME	= minishell
CC		= cc
# CFLAGS	= -Wall -Wextra -Werror
CFLAGS	= -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include -g3 
#   CFLAGS	= -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include  # -fsanitize=address -g3
LDFLAGS	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib 
#  LDFLAGS	= -lreadline -L /opt/homebrew/opt/readline/lib 
#SFLAGS	= -g3 -fsanitize=address

FILES	=	srcs/main \
			srcs/free_shell \
			srcs/parse_input/parser \
			srcs/parse_input/build_cmd \
			srcs/parse_input/build_pipe \
			srcs/parse_input/build_io \
			srcs/parse_input/build_variable \
			srcs/parse_input/build_variable_utils \
			srcs/parse_input/build_split \
			srcs/parse_input/build_split_utils \
			srcs/parse_input/handle_quotes \
			srcs/errors \
			srcs/gethings \
			srcs/get_things_aux \
			srcs/utilslist \
			srcs/builtins/cd \
			srcs/builtins/echo \
			srcs/builtins/export \
			srcs/builtins/export_utils \
			srcs/builtins/unset \
			srcs/builtins/exit \
			srcs/builtins/pwd \
			srcs/pipes/cmd_handler \
			srcs/pipes/manage_files \
			srcs/pipes/process_utils \
			srcs/pipes/pipes_utils \
			srcs/pipes/run_pipes \
			srcs/pipes/aux_run_pipes


CFILES	= $(addsuffix .c, $(FILES))
OBJS	= $(addsuffix .o, $(FILES))
HEADERS	= includes/
LIBFT_DIR	= srcs/libft
LEXER_DIR	= srcs/lexer

all: $(NAME) 

.c.o: $(CFILES)
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft $(LDFLAGS)

fsanitize:
	$(eval CFLAGS +=-fsanitize=address -g3)

sanitize: fsanitize all

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf *.dSYM
	rm - srcs/libft/libft.a

re: fclean all

.PHONY: all clean fclean re
