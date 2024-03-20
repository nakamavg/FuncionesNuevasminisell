NAME	= minishell
CC		= clang
CFLAGS	= -Wall -Wextra -Werror
SFLAGS	= -g3 -fsanitize=address

FILES	=	srcs/main \
			srcs/testers \
			srcs/parse_input/parser \
			srcs/parse_input/build_cmd \
			srcs/parse_input/build_pipe \
			srcs/parse_input/build_io \
			srcs/parse_input/build_variable \
			srcs/parse_input/build_split \

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
	$(CC) $(CFLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft
	# $(CC) $(SFLAGS) $(CFLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft

fsanitize:
	$(eval CFLAGS +=-fsanitize=address -g3)

sanitize: fsanitize all

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf *.dSYM
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
