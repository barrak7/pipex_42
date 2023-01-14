/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:55:18 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/10 11:55:37 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t sl;
	size_t dl;
	size_t s;

	if (!src || (!dst && dstsize))
		return (0);
	sl = ft_strlen(src);
	if (!dst && !dstsize)
		return (sl);
	dl = ft_strlen(dst);
	s = dstsize - dl;
	if (dstsize == 0 || dstsize <= dl)
		return (sl + dstsize);
	ft_strlcpy(&dst[dl], src, s);
	return (sl + dl);
}
