/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:11:02 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/02 08:20:56 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *saver, char *buff)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (ft_strlen(saver) + ft_strlen(buff) + 1));
	i = 0;
	while (saver[i])
	{
		str[i] = saver[i];
		i++;
	}
	while (*buff)
	{
		str[i] = *buff;
		buff++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
