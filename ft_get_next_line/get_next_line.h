/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:43:18 by ael-moha          #+#    #+#             */
/*   Updated: 2024/02/15 18:59:15 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_getline(char *remain);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, size_t start, size_t len);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_joinfree(char **remain, char **buffer, ssize_t bytesread);
int		ft_strchr(char *s, int c);
char	*ft_readfile(int fd, char **res);

#endif
