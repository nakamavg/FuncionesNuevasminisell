/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:17:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/28 00:05:49 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define FD_STDOUT 1
# define FD_STDERR 2
# define MAX_INT_LEN 12
# define MAX_LONG_LEN 22
# define HEXL "0123456789abcdef"
# define HEXU "0123456789ABCDEF"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalnum(int c);
int					ft_tolower(int c);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
void				*ft_memchr(const void *str, int c, size_t n);
void				*ft_memset(void *buffer, int val, size_t len);
void				ft_bzero(void *buffer, size_t len);
void				*ft_memmove(void *dest, const void *src, size_t n);
int					ft_toupper(int c);
char				*ft_strrchr(const char *str, int c);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalpha(int c);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isprint(int c);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *str1);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isascii(int c);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t loc);
int					ft_isdigit(int c);
char				*ft_strchr(const char *str, int c);
void				*ft_memcpy(void *dest, const void *src,
						size_t bytes_copied);
int					ft_atoi(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *list);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// Sprintf && Sprintf Utils:
char				*ft_sprintf(char const *container, ...);
char				*ft_puthexa_str(size_t n);
char				*ft_putaddress_str(unsigned long p);
char				*str_or_null(const char *str);

// Printf && Printf utils
int					ft_printf(const char *fmt, ...);
int					ft_printstr(char *s);
int					ft_printnbr(long nbr, int base, char *nbr_formatter);
int					ft_printchar(int c);
int					ft_print_addr(unsigned long nbr,
						int base, char *nbr_formatter);

// fd_printf && fd_printf utils
int					ft_fd_printf(int fd, const char *fmt, ...);
int					ft_fd_printstr(int fd, char *s);
int					ft_fd_printnbr(int fd, long nbr, int base,
						char *nbr_formatter);
int					ft_fd_printchar(int fd, int c);
int					ft_fd_print_addr(int fd, unsigned long nbr,
						int base, char *nbr_formatter);

// Get next line 
char				*get_next_line(int fd);

#endif
