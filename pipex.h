/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:20:54 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/04 20:53:08 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct t_llist{
	char			**cmd1;
	char			**cmd2;
	char			*cmd_path;
	char			*argv;
	struct t_llist	*athr;
}					t_list;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *str1, char *str2);
char	*get_path(char **envp, char *to_find, char *cmd_or_file);
void	error_function(int x, char *str);
void	ft_putstr_fd(char *s, int fd);
void	mix_function(t_list *ptr1, t_list *ptr2, char *av1, char *av2);
void	extra_err_function(char *str);

#endif