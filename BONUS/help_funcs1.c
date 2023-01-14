/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:53:14 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 21:35:22 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	f_finish(int pip_fd[2][2], int c1, t_elem vars)
{
	int	status;

	close(pip_fd[1][0]);
	close(pip_fd[1][1]);
	close(pip_fd[0][0]);
	close(pip_fd[0][1]);
	if (vars.herdoc)
		unlink("pipex_heredoc.txt");
	waitpid(c1, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

void	check_argc(t_elem vars)
{
	if (vars.c < 2)
	{
		write(2, "Invalid Syntax!\n", 16);
		exit(1);
	}
}

void	sec_child(int *i, t_elem vars, int pip_fd[2][2])
{
	int	c;

	if ((*i) + 1 < vars.c - 1)
		close(pip_fd[0][0]);
	close(pip_fd[0][1]);
	close(pip_fd[1][1]);
	if (pipe(pip_fd[0]) == -1)
		exit(1);
	if ((*i) + 1 < vars.c - 1)
	{
		c = fork();
		if (!c)
			exec_c(pip_fd[1], pip_fd[0], vars.cmds[(*i) + 1], vars.path);
		else
			close(pip_fd[1][0]);
	}
	(*i) += 2;
}

void	read_herdoc(t_elem *vars, char *limiter)
{
	char	*buffer;

	while (1)
	{
		write(1, "heredoc>", 9);
		buffer = get_next_line(0);
		if (!ft_strncmp(limiter, buffer, ft_strlen(limiter))
			&& buffer[ft_strlen(limiter)] == '\n')
			break ;
		write(vars->fd_in, buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(vars->fd_in);
	vars->fd_in = open("pipex_heredoc.txt", O_RDONLY);
}

void	init_n_check(t_elem *vars, char **argv, int argc, char **envp)
{
	if (ft_strncmp(argv[1], "here_doc", 9))
		vars->herdoc = 0;
	else
		vars->herdoc = 1;
	if (vars->herdoc)
	{
		vars->c = argc - 4;
		check_argc(*vars);
		vars->fd_in = open("pipex_heredoc.txt", O_CREAT | O_WRONLY, 0666);
		vars->fd_out = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT,
				0666);
		read_herdoc(vars, argv[2]);
		vars->cmds = &argv[3];
	}
	else
	{
		vars->c = argc - 3;
		check_argc(*vars);
		vars->fd_in = open(argv[1], O_RDONLY, 0666);
		if (vars->fd_in == -1)
			perror(argv[1]);
		vars->fd_out = open(argv[argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0666);
		vars->cmds = &argv[2];
	}
	vars->path = get_path(envp);
}
