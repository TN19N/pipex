/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:04:45 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/02 07:20:08 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	**ft_split(char const *s, char c);
char	*get_path(char **envp);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *saver, char *buff);
char *check_if_access(char *full_path, char *cmd);

#endif