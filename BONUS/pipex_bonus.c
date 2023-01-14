/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:09:33 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 18:15:15 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	err_ex(char *err)
{
	perror(err);
	exit(1);
}

int	check_del(char *del, char *buffer)
{
	if (ft_strncmp(del, buffer, ft_strlen(del)) == 0
		&& buffer[ft_strlen(del)] == '\n')
		return (1);
	return (0);
}

int	init_fd(char **argv)
{
	int		fd;
	char	*buffer;

	if (ft_strncmp(argv[1], "here_doc", 9))
		fd = open(argv[1], O_RDONLY);
	else
	{
		fd = open("pipex_herdoc.txt", O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (fd == -1)
			exit(1);
		while (1)
		{
			write(1, "heredoc>", 8);
			buffer = get_next_line(0);
			if (check_del(argv[2], buffer))
			{
				free(buffer);
				break ;
			}
			write(fd, buffer, ft_strlen(buffer));
			free(buffer);
		}
		close(fd);
		fd = open("pipex_herdoc.txt", O_RDONLY);
	}
	return (fd);
}

void	exec_f(int *pip_fd, char **argv, char *path)
{
	char	*file;
	int		i;
	int		fd;
	char	**cmd;

	i = 0;
	close(pip_fd[0]);
	fd = init_fd(argv);
	if (fd == -1)
		err_ex("ERROR");
	if (dup2(fd, 0) == -1)
		exit(1);
	if (dup2(pip_fd[1], 1) == -1)
		exit(1);
	if (ft_strncmp("here_doc", argv[1], 9))
		cmd = ft_split(argv[2], ' ');
	else
		cmd = ft_split(argv[3], ' ');
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

void	exec_l(int *pip_fd, char **argv, char *path, int argc)
{
	char	*file;
	int		i;
	int		fd;
	char	**cmd;

	i = 0;
	if (ft_strncmp("here_doc", argv[1], 9))
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	close(pip_fd[1]);
	if (fd == -1)
		err_ex(argv[5]);
	if (dup2(pip_fd[0], 0) == -1)
		exit(1);
	if (dup2(fd, 1) == -1)
		exit(1);
	cmd = ft_split(argv[argc - 2], ' ');
	if (!cmd)
		exit(1);
	file = get_cmd(cmd[0], path);
	if (execve(file, cmd, NULL) == -1)
		check_access(cmd[0], file);
}

void	f_finish(int pip_fd[2][2], int c1)
{
	int	status[2];

	close(pip_fd[1][0]);
	close(pip_fd[1][1]);
	close(pip_fd[0][0]);
	close(pip_fd[0][1]);
	waitpid(c1, &status[0], 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status[1]))
		exit(WEXITSTATUS(status[1]));
}

void	check_argc(int c)
{
	if (c < 5)
	{
		write(2, "Invalid Syntax!\n", 16);
		exit(1);
	}
}

void	sec_child(int i, int argc, char **argv, char *path, int pip_fd[2][2])
{
	int	c;

	if (i + 1 < argc - 2)
		close(pip_fd[0][0]);
	close(pip_fd[0][1]);
	close(pip_fd[1][1]);
	if (pipe(pip_fd[0]) == -1)
		exit(1);
	if (i + 1 < argc - 2)
	{
		c = fork();
		if (!c)
			exec_c(pip_fd[1], pip_fd[0], argv[i + 1], path);
		else
			close(pip_fd[1][0]);
	}
}

void	init_n_check(t_elem vars, char **argv, int argc, char *path)
{
}

int	main(int argc, char **argv, char **envp)
{
	int		c;
	int		pip_fd[2][2];
	char	*path;
	t_elem	vars;
	int		i;

	path = get_path(envp);
	init_n_check(vars, argv, argc, path);
	if (ft_strncmp(argv[1], "here_doc", 9))
		i = 2;
	else
		i = 3;
	check_argc(argc);
	if (pipe(pip_fd[0]) == -1)
		exit(1);
	c = fork();
	if (c == -1)
		exit(1);
	if (!c)
		exec_f(pip_fd[0], argv, path);
	else
	{
		while (i < argc - 2)
		{
			if (pipe(pip_fd[1]) == -1)
				exit(1);
			c = fork();
			if (!c)
				exec_c(pip_fd[0], pip_fd[1], argv[i], path);
			else
			{
				sec_child(i, argc, argv, path, pip_fd);
				i += 2;
			}
		}
		c = fork();
		if (!c)
		{
			if (ft_strncmp("here_doc", argv[1], 9) && argc % 2 == 0)
			{
				close(pip_fd[1][0]);
				close(pip_fd[1][1]);
				exec_l(pip_fd[0], argv, path, argc);
			}
			else
			{
				close(pip_fd[0][0]);
				close(pip_fd[0][1]);
				exec_l(pip_fd[1], argv, path, argc);
			}
		}
		else
			f_finish(pip_fd, c);
	}
	return (0);
}
