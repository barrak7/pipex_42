/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:50:32 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 21:21:49 by hbarrak          ###   ########.fr       */
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

typedef struct s_elem
{
	int		c;
	char	**cmds;
	int		herdoc;
	char	*path;
	int		fd_in;
	int		fd_out;
}			t_elem;

int			is_path(char *cmd);
int			*get_pipe(int c, int pip_fd[2][2]);

char		*check_f(char *cmd, char *path);
char		*get_cmd(char *cmd, char *path);
char		*get_path(char **envp);

void		f_finish(int pip_fd[2][2], int c1, t_elem vars);
void		init_file(char **file, char *path, char *cmd);
void		check_access(char *cmd, char *file);
void		check_argc(t_elem vars);
void		sec_child(int *i, t_elem vars, int pip_fd[2][2]);
void		read_herdoc(t_elem *vars, char *limiter);
void		init_n_check(t_elem *vars, char **argv, int argc, char **envp);
void		err_ex(char *err);
void		exec_c(int *pip_fd1, int *pip_fd2, char *arg, char *path);

#endif
