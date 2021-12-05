/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:19:43 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/04 21:14:00 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_function(char **str1, char **str2, char *str3, int x)
{
	int	i;

	i = -1;
	if (str1)
	{
		while (str1[++i])
			free(str1[i]);
		free(str1);
	}
	i = -1;
	if (str2)
	{
		while (str2[++i])
			free(str2[i]);
		free(str2);
	}
	if (str3 && x != 2)
		free(str3);
	if (x == 0)
		error_function(0, NULL);
	else if (x == 2)
		extra_err_function(str3);
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

static void	main_process(char **envp, int *fd, t_list *cmds2, char *file2)
{
	int	fld;

	wait(NULL);
	cmds2->cmd_path = get_path(envp, "PATH=", cmds2->cmd2[0]);
	if (!cmds2->cmd_path && access(cmds2->cmd2[0], F_OK) == 0)
		free_function(cmds2->cmd2, cmds2->athr->cmd1, cmds2->argv, 2);
	else if (!cmds2->cmd_path)
		free_function(cmds2->cmd2, cmds2->athr->cmd1, NULL, 0);
	fld = open(file2, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fld == -1)
		free_function(cmds2->cmd2, cmds2->athr->cmd1, cmds2->cmd_path, 1);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		free_function(cmds2->cmd2, cmds2->athr->cmd1, cmds2->cmd_path, 0);
	if (dup2(fld, STDOUT_FILENO) == -1)
		free_function(cmds2->cmd2, cmds2->athr->cmd1, cmds2->cmd_path, 0);
	close(fd[0]);
	close(fld);
	if (execve(cmds2->cmd_path, cmds2->cmd2, envp) == -1)
		free_function(cmds2->cmd2, cmds2->athr->cmd1, cmds2->cmd_path, 0);
}

static void	child_process(char **envp, int *fd, t_list *cmds1, char *file1)
{
	int	fld;

	fld = open(file1, O_RDONLY);
	if (fld == -1)
	{
		free_function(cmds1->cmd1, cmds1->athr->cmd2, NULL, 1);
		error_function(2, file1);
	}
	cmds1->cmd_path = get_path(envp, "PATH=", cmds1->cmd1[0]);
	if (!cmds1->cmd_path && access(cmds1->cmd1[0], F_OK) == 0)
		free_function(cmds1->cmd1, cmds1->athr->cmd2, cmds1->argv, 2);
	else if (!cmds1->cmd_path)
		free_function(cmds1->cmd1, cmds1->athr->cmd2, NULL, 1);
	close(fd[0]);
	if (dup2(fld, STDIN_FILENO) == -1)
		free_function(cmds1->cmd1, cmds1->athr->cmd2, cmds1->cmd_path, 0);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		free_function(cmds1->cmd1, cmds1->athr->cmd2, cmds1->cmd_path, 0);
	close(fd[1]);
	close(fld);
	if (execve(cmds1->cmd_path, cmds1->cmd1, envp) == -1)
		free_function(cmds1->cmd1, cmds1->athr->cmd2, cmds1->cmd_path, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	cmds1;
	t_list	cmds2;
	int		frk;
	int		fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("pipex: usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n", 2);
		exit(-1);
	}
	if (pipe(fd) == -1)
		error_function(0, NULL);
	cmds1.cmd1 = ft_split(argv[2], ' ');
	cmds2.cmd2 = ft_split(argv[3], ' ');
	mix_function(&cmds1, &cmds2, argv[2], argv[3]);
	if (!cmds1.cmd1 || !cmds2.cmd2)
		free_function(cmds1.cmd1, cmds2.cmd2, NULL, 0);
	frk = fork();
	if (frk == -1)
		free_function(cmds1.cmd1, cmds2.cmd2, NULL, 0);
	if (frk == 0)
		child_process(envp, fd, &cmds1, argv[1]);
	else
		main_process(envp, fd, &cmds2, argv[4]);
	return (0);
}
