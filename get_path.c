/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:33:57 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/03 14:33:28 by mannouao         ###   ########.fr       */
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
		check = access(path_holder, F_OK);
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

char	*get_path(char **envp, char *to_find, char *cmd_or_file)
{
	char	*full_path;
	char	**pathes;
	int		len;
	char	*the_path;

	len = ft_strlen(to_find);
	full_path = get_full_path(envp, to_find);
	if (!full_path)
		error_function();
	if (len == 5)
	{
		pathes = ft_split(full_path + len, ':');
		the_path = find_the_path(pathes, cmd_or_file);
		if (!the_path)
			error_function();
	}
	else
	{
		full_path = ft_strjoin(full_path, "/");
		the_path = ft_strjoin(full_path + len, cmd_or_file);
	}
	return (the_path);
}
