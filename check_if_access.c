/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:12:09 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/02 11:15:14 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *check_if_access(char *full_path, char *cmd_or_file, int chose)
{
	int	i;
	char **paths;
	char *mini_path;

	i = 0;
	if(chose == 1)
		paths = ft_split(full_path, ':');
	else
	{
		paths = (char **)malloc(sizeof(char *) * 2);
		if(!paths)
		{
			perror("check_if_access.c (26) : allocation faild");
			exit(errno);
		}
		paths[0] = full_path;
		paths[1] = NULL;
	}
	while(paths[i])
	{
		mini_path = ft_strjoin(paths[i], "/");
		if(!access(ft_strjoin(mini_path, cmd_or_file), F_OK))
			return (ft_strjoin(mini_path, cmd_or_file));
		i++;
	}
	return (NULL);
}