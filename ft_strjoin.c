/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:02:42 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/03 14:29:52 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*str;
	int		i;

	if(!str1 || !str2)
		error_function();
	str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	i = 0;
	while (str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	while (*str2)
	{
		str[i] = *str2;
		str2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
