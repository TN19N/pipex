/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:12:09 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/02 08:12:18 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *check_if_access(char *full_path, char *cmd)
{
	int	i;
	char **paths;
	char *mini_path;

	i = 0;
	paths = ft_split(full_path, ':');
	while(paths[i])
	{
		mini_path = ft_strjoin(paths[i], "/");
		if(!access(ft_strjoin(mini_path, cmd), F_OK))
			return (ft_strjoin(mini_path, cmd));
		i++;
	}
	return (NULL);
}