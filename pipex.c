/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:19:43 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/04 15:49:36 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_function(char **str1, char **str2, char *str3)
{
	int	i;

	i = 0;
	if (str1)
	{
		while (str1[i])
		{
			free(str1[i]);
			i++;
		}
		free(str1);
	}
	if (str2)
	{
		while (str2[i])
		{
			free(str2[i]);
			i++;
		}
		free(str2);
	}
	if (str3)
		free(str3);
	error_function(0, NULL);
}

void	error_function(int x, char *str)
{
	if (x == 0)
	{
		perror("pipex");
		if (errno != 0)
			exit(errno);
		else
			exit(-1);
	}
	else if (x == 1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
		exit(-1);
	}
	else if (x == 2)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
		exit(errno);
	}
}

static void	main_process(char **envp, int *fd, char **cmd2, char *file2)
{
	char	*cmd2_path;
	char	*file2_path;
	int		fld;

	wait(NULL);
	file2_path = get_path(envp, "PWD=", file2);
	cmd2_path = get_path(envp, "PATH=", cmd2[0]);
	if (!cmd2_path)
		fld = -1;
	else
		fld = open(file2_path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	free(file2_path);
	if (fld == -1)
		error_function(0, NULL);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		free_function(cmd2, NULL, cmd2_path);
	if (dup2(fld, STDOUT_FILENO) == -1)
		free_function(cmd2, NULL, cmd2_path);
	close(fd[0]);
	close(fld);
	if (execve(cmd2_path, cmd2, envp) == -1)
		free_function(cmd2, NULL, cmd2_path);
}

static void	child_process(char **envp, int *fd, char **cmd1, char *file1)
{
	char	*cmd1_path;
	char	*file1_path;
	int		fld;

	file1_path = get_path(envp, "PWD=", file1);
	fld = open(file1_path, O_RDONLY);
	free(file1_path);
	if (fld == -1)
		error_function(2, file1);
	cmd1_path = get_path(envp, "PATH=", cmd1[0]);
	//close(fd[0]);
	if (dup2(fld, STDIN_FILENO) == -1)
		free_function(cmd1, NULL, cmd1_path);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		free_function(cmd1, NULL, cmd1_path);
	//close(fd[1]);
	close(fld);
	if (execve(cmd1_path, cmd1, envp) == -1)
		free_function(cmd1, NULL, cmd1_path);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**command1;
	char	**command2;
	int		frk;
	int		fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("pipex: usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n", 2);
		exit(-1);
	}
	if (pipe(fd) == -1)
		error_function(0, NULL);
	command1 = ft_split(argv[2], ' ');
	command2 = ft_split(argv[3], ' ');
	if (!command1 || !command2)
		free_function(command1, command2, NULL);
	frk = fork();
	if (frk == -1)
		free_function(command1, command2, NULL);
	if (frk == 0)
		child_process(envp, fd, command1, argv[1]);
	else
		main_process(envp, fd, command2, argv[4]);
	return (0);
}
