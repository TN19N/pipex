/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:08:49 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/02 08:12:28 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void fill(char *path, char *envp)
{
	int	i;
	int	j;

	i = 0;
	j = 5;
	while(envp[j])
	{
		path[i] = envp[j];
		i++;
		j++;
	}
	path[i] = '\0';
}

char	*get_path(char **envp)
{
	int	i;
	int	j;
	char find[] = "PATH";
	char *path;

	i = 0;
	path = NULL;
	while(envp[i])
	{
		j = 0;
		while(envp[i][j] && find[j])
		{
			if(envp[i][j] != find[j])
				break ;
			j++;
		}
		if(!find[j])
		{
			path = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) - 4));
			if(!path)
				return (NULL);
			fill(path, envp[i]);
			break ;
		}
		i++;
	}
	return (path);
}