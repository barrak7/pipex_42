/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:54:34 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/10 11:55:04 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s, char const *s1)
{
	char	*p;
	size_t	al;

	if (!s || !s1)
		return (0);
	al = ft_strlen(s) + ft_strlen(s1) + 1;
	p = ft_calloc(al, sizeof(char));
	if (p)
	{
		ft_strlcat(p, s, al);
		ft_strlcat(p, s1, al);
	}
	return (p);
}
