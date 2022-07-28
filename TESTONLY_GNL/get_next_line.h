/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokrokhi <kokrokhi@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:21 by Konstantin        #+#    #+#             */
/*   Updated: 2022/07/22 18:20:23 by kokrokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	gnl_strlen1(const char *s);
void	*ft_memmove1(void *dst, const void *src, size_t len);
char	*ft_strchr1(const char *s, int c);
void	*ft_memset1(void *b, int c, size_t len);
char	*gnl_calloc(int count);

#endif