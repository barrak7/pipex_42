/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:31:21 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 21:03:07 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strtrim_nl(char *str);
char	*ft_substr(char *src, int start, size_t len);
int		found_nl(char *dst, char **leftovers);

#endif
