/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:52:52 by hbarrak           #+#    #+#             */
/*   Updated: 2023/01/12 14:46:28 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	check_access(char *cmd, char *file)
{
	if (!file)
	{
		write(2, "pipex: Command not found: ", 26);
		write(2, cmd, ft_strlen(cmd));
		write(2, "\n", 1);
		exit(1);
	}
	else if (access(file, X_OK) == -1)
	{
		perror(cmd);
		exit(1);
	}
	else
		exit(1);
}

char	*check_f(char *cmd, char *path)
{
	char	**tmp;
	char	*t_file;
	char	*file;

	tmp = ft_split(path, '=');
	t_file = ft_strjoin(tmp[1], "/");
	file = ft_strjoin(t_file, cmd);
	free(t_file);
	if (!access(file, F_OK))
	{
		fr_s(tmp);
		return (file);
	}
	fr_s(tmp);
	free(file);
	return (0);
}

void	init_file(char **file, char *path, char *cmd)
{
	char	*t_file;

	t_file = ft_strjoin(path, "/");
	*file = ft_strjoin(t_file, cmd);
	free(t_file);
}

char	*get_cmd(char *cmd, char *path)
{
	char	**paths;
	char	*file;
	int		i;

	i = 0;
	if (is_path(cmd))
		return (cmd);
	paths = ft_split(path, ':');
	while (paths[i])
	{
		if (i == 0 && check_f(cmd, paths[i]))
			return (check_f(cmd, paths[i]));
		init_file(&file, paths[i], cmd);
		if (!access(file, F_OK))
		{
			fr_s(paths);
			return (file);
		}
		free(file);
		i++;
	}
	fr_s(paths);
	return (0);
}
