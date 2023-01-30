/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:02:14 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/30 15:34:13 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_f(int *pip_fd, char **argv, char *path)
{
	char	*file;
	int		i;
	int		fd;
	char	**cmd;

	i = 0;
	close(pip_fd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	if (dup2(fd, 0) == -1)
		exit(1);
	if (dup2(pip_fd[1], 1) == -1)
		exit(1);
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		exit(1);
	file = get_cmd(cmd[0], path);
	if (execve(file, cmd, NULL) == -1)
		check_access(cmd[0], file);
}

void	exec_l(int *pip_fd, char **argv, char *path)
{
	char	*file;
	int		i;
	int		fd;
	char	**cmd;

	i = 0;
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	close(pip_fd[1]);
	if (fd == -1)
	{
		perror(argv[4]);
		exit(1);
	}
	if (dup2(pip_fd[0], 0) == -1)
		exit(1);
	if (dup2(fd, 1) == -1)
		exit(1);
	cmd = ft_split(argv[3], ' ');
	if (!cmd)
		exit(1);
	file = get_cmd(cmd[0], path);
	if (execve(file, cmd, NULL) == -1)
		check_access(cmd[0], file);
}

void	f_finish(int *pip_fd, int c1, int c2)
{
	int	status[2];

	close(pip_fd[1]);
	close(pip_fd[0]);
	waitpid(c1, &status[0], 0);
	waitpid(c2, &status[1], 0);
	if (WIFEXITED(status[1]))
		exit(WEXITSTATUS(status[1]));
}

void	check_argc(int c)
{
	if (c != 5)
	{
		write(2, "Invalid Syntax!\n", 16);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		c;
	int		pip_fd[2];
	char	*path;
	int		c2;

	check_argc(argc);
	path = get_path(envp);
	if (pipe(pip_fd) == -1)
		exit(1);
	c = fork();
	if (c == -1)
		exit(1);
	if (!c)
		exec_f(pip_fd, argv, path);
	else
	{
		c2 = fork();
		if (!c2)
			exec_l(pip_fd, argv, path);
		else
			f_finish(pip_fd, c, c2);
	}
	return (0);
}
