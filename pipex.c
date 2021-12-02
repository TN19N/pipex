/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:19:43 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/02 16:57:41 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char *file)
{
	
}

int main(int argc, char *argv[], char *envp[])
{
	char **commands1;
	char **commands2;
	char *file1_path;
	char *path1,
	char *path2;
	char *pwd;
	
	if(argc != 5)
		return (1);
	commands1 = ft_split(argv[2], ' ');
	commands2 = ft_split(argv[3], ' ');
	file1_path = find_path(argv[1]);
	path1 = get_path(envp, "PATH=", commands1[0]);
	path2 = get_path(envp, "PATH=", commands2[0]);
	pwd = get_path(envp, "PWD=");
}