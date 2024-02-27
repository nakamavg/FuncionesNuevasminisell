# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 18:30:09 by alberrod          #+#    #+#              #
#    Updated: 2024/01/28 00:00:58 by alberrod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = cc
HEADERS_DIR = .
CFLAGS   = -Wall -Wextra -Werror -I $(HEADERS_DIR)
NAME     = libft.a
RM       = rm -rf

CFILES = ft_calloc.c ft_isdigit.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
	   ft_strjoin.c	ft_strmapi.c ft_strtrim.c ft_isalnum.c	\
	   ft_isprint.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcat.c \
	   ft_strncmp.c	ft_substr.c ft_atoi.c ft_isalpha.c ft_itoa.c \
	   ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlcpy.c ft_strnstr.c \
	   ft_tolower.c ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c \
	   ft_putstr_fd.c ft_striteri.c ft_strlen.c ft_strrchr.c ft_toupper.c \
	   ft_sprintf.c sprintf_utils.c \
	   ft_printf.c printers.c \
	   ft_fd_printf.c fd_printers.c \
	   get_next_line.c

OFILES = $(CFILES:.c=.o)

CBONUSS = ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstmap_bonus.c \
		  ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c \
		  ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c

OBONUSS = $(CBONUSS:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

bonus: $(OBONUSS)
	ar rcs $(NAME) $(OBONUSS)

clean:
	$(RM) $(OFILES) $(OBONUSS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME) bonus

.PHONY: all clean fclean re
 
# BONUSS = $(wildcard $(BONUS_DIR)/*.c)
# OBJS := $(SCRS:.c=.o)

# all: $(NAME)

# ${OBJ_DIR}:
# 	mkdir -p ${OBJ_DIR}

# ${OBJ_DIR}/%.o: ${SRCS} | ${OBJ_DIR}
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): ${OBJ_DIR} ${OBJS}
# 	ar rc $(NAME) $(OBJS)
	

# ${BONUS_OBJ_DIR}:
# 	mkdir -p $(BONUS_OBJ_DIR)

# BONUS_OBJS := $(patsubst ${BONUS_DIR}/%.c, ${BONUS_OBJ_DIR}/%.o, ${BONUSS})

# ${BONUS_OBJ_DIR}/%.o: ${BONUS_DIR}/%.c | ${BONUS_OBJ_DIR}
# 	$(CC) $(CFLAGS) -c $< -o $@

# bonus: ${BONUS_OBJ_DIR} ${BONUS_OBJS}
# 	ar rc $(NAME) $(BONUS_OBJS)
# 	ranlib $(NAME)

# clean:
# 	$(RM) $(OBJ_DIR) $(BONUS_OBJ_DIR)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
