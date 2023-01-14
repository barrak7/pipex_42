/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:02:22 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/11 21:50:16 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		is_path(char *cmd);
void	check_access(char *cmd, char *file);
char	*check_f(char *cmd, char *path);
void	init_file(char **file, char *path, char *cmd);
char	*get_cmd(char *cmd, char *path);
char	*get_path(char **envp);

#endif
