/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:43:54 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/10 21:53:22 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;
size_t			ft_strlen(char const *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
int				ft_isprint(int sym);
int				ft_isalpha(int sym);
int				ft_isdigit(int sym);
int				ft_isalnum(int sym);
int				ft_isascii(int sym);
int				ft_atoi(char const *str);
int				ft_toupper(int sym);
int				ft_tolower(int sym);
int				ft_strcmp(char const *str1, char const *str2);
int				ft_memcmp(void const *str1, void const *str2, size_t n);
int				perror_return_number(char *str, int num);
void			*ft_memchr(const void *str, int sym, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *str, int sym, size_t n);
void			ft_bzero(void *str, size_t n);
void			*ft_memccpy(void *dest, const void *src, int sym, size_t n);
void			*ft_calloc(size_t n, size_t size);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			putstr_exit(char *str);
void			perror_exit(char *str);
void			perror_return(char *str);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strdup(const char *str);
char			*ft_strchr(const char *str, int sym);
char			*ft_strrchr(const char *str, int sym);
char			*ft_itoa(int n);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strnstr(const char *big, const char *little, size_t n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_strcpy(char *dst, const char *src);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
int				ft_lstsize(t_list *lst);
int				error_return(char *str);
int				is_all_spaces(char *str);
long			max(long a, long b);
long			min(long a, long b);
long long int	atoi_overflow(const char *str);

#endif
