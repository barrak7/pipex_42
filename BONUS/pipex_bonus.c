/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:09:33 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 21:33:38 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_f(int *pip_fd, t_elem vars, char *path)
{
	char	*file;
	int		i;
	char	**cmd;

	i = 0;
	close(pip_fd[0]);
	if (vars.fd_in == -1)
		exit(1);
	if (dup2(vars.fd_in, 0) == -1)
		exit(1);
	if (dup2(pip_fd[1], 1) == -1)
		exit(1);
	cmd = ft_split(vars.cmds[0], ' ');
	if (!cmd)
		exit(1);
	file = get_cmd(cmd[0], path);
	if (execve(file, cmd, NULL) == -1)
		check_access(cmd[0], file);
}

void	exec_c(int *pip_fd1, int *pip_fd2, char *arg, char *path)
{
	char	*file;
	char	**cmd;

	close(pip_fd1[1]);
	close(pip_fd2[0]);
	if (dup2(pip_fd1[0], 0) == -1)
		exit(1);
	if (dup2(pip_fd2[1], 1) == -1)
		exit(1);
	cmd = ft_split(arg, ' ');
	file = get_cmd(cmd[0], path);
	if (execve(file, cmd, NULL) == -1)
		check_access(cmd[0], file);
}

void	exec_l(int pip_fd[2][2], t_elem vars)
{
	char	*file;
	char	**cmd;
	int		*pip;

	pip = get_pipe(vars.c, pip_fd);
	if (vars.fd_out == -1)
		err_ex(vars.cmds[vars.c]);
	if (dup2(pip[0], 0) == -1)
		exit(1);
	if (dup2(vars.fd_out, 1) == -1)
		exit(1);
	cmd = ft_split(vars.cmds[vars.c - 1], ' ');
	if (!cmd)
		exit(1);
	file = get_cmd(cmd[0], vars.path);
	if (execve(file, cmd, NULL) == -1)
		check_access(cmd[0], file);
}

void	pipex_app(int i, t_elem vars, int pip_fd[2][2])
{
	int	c;

	while (i < vars.c - 1)
	{
		if (pipe(pip_fd[1]) == -1)
			exit(1);
		c = fork();
		if (!c)
			exec_c(pip_fd[0], pip_fd[1], vars.cmds[i], vars.path);
		else
			sec_child(&i, vars, pip_fd);
	}
	c = fork();
	if (!c)
		exec_l(pip_fd, vars);
	else
		f_finish(pip_fd, c, vars);
}

int	main(int argc, char **argv, char **envp)
{
	int		c;
	int		pip_fd[2][2];
	t_elem	vars;
	int		i;

	init_n_check(&vars, argv, argc, envp);
	if (pipe(pip_fd[0]) == -1)
		exit(1);
	c = fork();
	if (c == -1)
		exit(1);
	i = 1;
	if (!c)
		exec_f(pip_fd[0], vars, vars.path);
	else
		pipex_app(i, vars, pip_fd);
	return (0);
}
