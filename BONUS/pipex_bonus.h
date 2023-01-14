/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:50:32 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 18:08:27 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int			is_path(char *cmd);
void		check_access(char *cmd, char *file);
char		*check_f(char *cmd, char *path);
void		init_file(char **file, char *path, char *cmd);
char		*get_cmd(char *cmd, char *path);
char		*get_path(char **envp);

typedef struct s_elem
{
	int		c;
	char	**cmds;
	int		herdoc;
	char	*path;
}			t_elem;

#endif
