/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokrokhi <kokrokhi@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:17 by Konstantin        #+#    #+#             */
/*   Updated: 2022/07/22 18:20:13 by kokrokhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef GET_NEXT_LINE_UTILS
# define GET_NEXT_LINE_UTILS

size_t	gnl_strlen1(const char *s)
{
	int	size;

	size = 0;
	if (!s)
		return (0);
	while (s[size] != '\0')
		size++;
	return (size);
}

void	*ft_memmove1(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}

void	*ft_memset1(void *b, int c, size_t len)
{
	size_t			n;
	unsigned char	*pt;

	pt = b;
	n = 0;
	while (n < len && pt)
	{
		*pt++ = c;
		n++;
	}
	return (b);
}

char	*ft_strchr1(const char *s, int c)
{
	char	*f;
	int		i;
	int		len;

	i = 0;
	f = (char *)s;
	len = gnl_strlen1(f);
	while (i <= len)
	{
		if (f[i] == (char)c)
			return (&f[i]);
		i++;
	}
	return (NULL);
}

char	*gnl_calloc(int count)
{
	char	*stringy;
	int		i;

	i = 0;
	stringy = malloc (count * sizeof(char));
	if (!stringy)
		return (NULL);
	while (i < count)
		stringy[i++] = '\0';
	return (stringy);
}

#endif