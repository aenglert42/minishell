/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: englot <englot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:13:45 by aenglert          #+#    #+#             */
/*   Updated: 2022/02/21 20:52:16 by englot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 512

typedef struct s_slist
{
	void			*content;
	struct s_slist	*next;
}	t_slist;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *node_to_add);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *node_to_add);
void	ft_dlstclear(t_dlist **lst, void (*del)(void *));
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstremove_node(t_dlist **lst, t_dlist *node_to_remove,
			void (*del)(void *));
char	*ft_gnl(int fd);
int		ft_hexlen(unsigned long n);
bool	ft_isalnum(int c);
bool	ft_isalpha(int c);
bool	ft_isascii(int c);
bool	ft_isdigit(int c);
bool	ft_isnumber(char *str);
bool	ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_slist **lst, t_slist *new);
void	ft_lstadd_front(t_slist **lst, t_slist *new);
void	ft_lstclear(t_slist **lst, void (*del)(void *));
void	ft_lstdelone(t_slist *lst, void (*del)(void *));
void	ft_lstiter(t_slist *lst, void (*f)(void *));
t_slist	*ft_lstlast(t_slist *lst);
t_slist	*ft_lstmap(t_slist *lst, void *(*f)(void *),
			void (*del)(void *));
t_slist	*ft_lstnew(void *content);
void	ft_lstremovenode(t_slist **lst, t_slist *node_to_remove,
			void (*del)(void *));
int		ft_lstsize(t_slist *lst);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy_c(void *dest, const void *src, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
int		ft_numlen(long long n);
int		ft_printf(const char *format, ...);
int		ft_printf_stderr(const char *format, ...);
void	ft_putchar_fd(char c, int fd);
int		ft_putcharret_fd(char c, int fd);
void	ft_puteol_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_putstrret_fd(char *s, int fd);
bool	ft_setcmp(char c, char *set);
char	**ft_split(char const *s, char c);
char	*ft_strappend(char const *s1, char const *s2);
int		ft_strappend2(char **s1, char const *s2);
size_t	ft_strcat_l(char *dst, const char *src, size_t dstsize);
char	*ft_strchr_r(const char *s, int c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp_n(const char *s1, const char *s2, size_t n);
bool	ft_strcmp(char *str1, char *str2);
size_t	ft_strcpy_l(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_strreplace(char **oldstr, char **newstr);
void	ft_strrev(char *str);
char	*ft_strstr_n(const char *haystack,
			const char *needle, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif