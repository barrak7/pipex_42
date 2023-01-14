/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:53:15 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/14 20:58:45 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && "PATH="[j] && envp[i][j] == "PATH="[j])
			j++;
		if (j == 5)
			break ;
		i++;
	}
	return (envp[i]);
}

void	err_ex(char *err)
{
	perror(err);
	exit(1);
}

int	*get_pipe(int c, int pip_fd[2][2])
{
	if (c % 2)
	{
		close(pip_fd[0][0]);
		close(pip_fd[0][1]);
		close(pip_fd[1][1]);
		return (pip_fd[1]);
	}
	close(pip_fd[1][0]);
	close(pip_fd[1][1]);
	close(pip_fd[0][1]);
	return (pip_fd[0]);
}
