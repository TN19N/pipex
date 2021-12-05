/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:33:57 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/04 21:13:43 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_the_path(char **pathes, char *path_to_find)
{
	int		i;
	char	*path_holder;
	char	*path_plas;
	int		check;

	i = 0;
	while (pathes[i])
	{
		path_plas = ft_strjoin(pathes[i], "/");
		path_holder = ft_strjoin(path_plas, path_to_find);
		check = access(path_holder, X_OK);
		free(path_plas);
		if (check == 0)
			return (path_holder);
		else
			free(path_holder);
		i++;
	}
	return (NULL);
}

static char	*get_full_path(char **envp, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && to_find[j])
		{
			if (envp[i][j] != to_find[j])
				break ;
			j++;
		}
		if (!to_find[j])
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*get_path(char **envp, char *to_find, char *cmd)
{
	char	*full_path;
	char	**pathes;
	char	*the_path;

	full_path = get_full_path(envp, to_find);
	if (full_path)
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == -1)
				return (NULL);
			return (cmd);
		}
		pathes = ft_split(full_path + 5, ':');
		the_path = find_the_path(pathes, cmd);
		if (!the_path)
			error_function(1, cmd);
		return (the_path);
	}
	return (NULL);
}

void	extra_err_function(char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd("pipex: Permission denied: ", 2);
	while (str[i] && str[i] != ' ')
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	exit(errno);
}
