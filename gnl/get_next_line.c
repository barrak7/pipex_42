/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:08:47 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 21:03:15 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	sl1;
	size_t	sl2;
	char	*p;

	i = 0;
	sl1 = ft_strlen(s1);
	sl2 = ft_strlen(s2);
	p = malloc(sl1 + sl2 + 1);
	while (i < sl1 && s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < sl2 && s2 && s2[i])
	{
		p[sl1] = s2[i];
		i++;
		sl1++;
	}
	p[sl1] = 0;
	if (s1)
		free(s1);
	return (p);
}

static char	*gnl_app(char *dst, char **leftovers, int fd)
{
	char	*tmp;
	int		r;

	tmp = 0;
	if (*leftovers)
		tmp = ft_strjoin(0, *leftovers);
	if (found_nl(tmp, leftovers))
		return (tmp);
	dst = malloc(BUFFER_SIZE + 1);
	if (dst)
		dst[0] = 0;
	while (dst && !found_nl(dst, leftovers))
	{
		r = read(fd, dst, BUFFER_SIZE);
		if (r <= 0)
			break ;
		dst[r] = 0;
		tmp = ft_strjoin(tmp, dst);
	}
	if (dst)
		free(dst);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*leftovers;
	char		*dst;

	dst = 0;
	dst = gnl_app(dst, &leftovers, fd);
	if (dst)
		dst = ft_strtrim_nl(dst);
	return (dst);
}
