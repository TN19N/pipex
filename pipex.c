/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:19:43 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/03 20:54:13 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_function(char **cmd1, char **cmd2)
{
	int i;

	i = 0;
	if(cmd1)
	{
		while(cmd1[i])
		{
			free(cmd1[i]);
			i++;
		}
		free(cmd1);
	}
	i = 0;
	if(cmd2)
	{
		while(cmd2[i])
		{
			free(cmd2[i]);
			i++;
		}
		free(cmd2);
	}
	perror("pipex");
	if(errno != 0)
		exit(errno);
	else
		exit(1);
}

static void	main_process(char **envp, int *fd, char **cmd2, char *file2)
{
	char	*cmd2_path;
	char	*file2_path;
	int		fld;

	wait(NULL);
	file2_path = get_path(envp, "PWD=", file2);
	cmd2_path = get_path(envp, "PATH=", cmd2[0]);
	fld = open(file2_path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fld == -1)
		error_function(NULL, NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fld, STDOUT_FILENO);
	close(fd[0]);
	close(fld);
	execve(cmd2_path, cmd2, envp);
}

static void	child_process(char **envp, int *fd, char **cmd1, char *file1)
{
	char	*cmd1_path;
	char	*file1_path;
	int		fld;

	file1_path = get_path(envp, "PWD=", file1);
	cmd1_path = get_path(envp, "PATH=", cmd1[0]);
	fld = open(file1_path, O_RDONLY);
	if (fld == -1)
		error_function(NULL, NULL);
	close(fd[0]);
	dup2(fld, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fld);
	execve(cmd1_path, cmd1, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**command1;
	char	**command2;
	int		frk;
	int		fd[2];

	if (argc != 5)
		error_function(NULL, NULL);
	if (pipe(fd) == -1)
		error_function(NULL, NULL);
	command1 = ft_split(argv[2], ' ');
	command2 = ft_split(argv[3], ' ');
	if(!command1 || !command2)
		error_function(command1, command1);
	frk = fork();
	if (frk == -1)
		error_function(NULL, NULL);
	if (frk == 0)
		child_process(envp, fd, command1, argv[1]);
	else
		main_process(envp, fd, command2, argv[4]);
	return (0);
}
