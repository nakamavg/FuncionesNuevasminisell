NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include -ggdb3 #-fsanitize=address -g3 
SFLAGS	= -g3 -fsanitize=address

FILES	= srcs/main srcs/gethings srcs/builtsin/builtsinhandler srcs/builtsin/cd srcs/builtsin/export \
		srcs/errors srcs/builtsin/unset srcs/utilslist srcs/builtsin/echo
CFILES	= $(addsuffix .c, $(FILES))
OBJS	= $(addsuffix .o, $(FILES))
HEADERS	= includes/
LIBFT_DIR	= srcs/libft
LDFLAGS	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib 

all: $(NAME) 

.c.o: $(CFILES)
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft && ./minishell

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