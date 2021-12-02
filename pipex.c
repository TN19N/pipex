/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:13:05 by mannouao          #+#    #+#             */
/*   Updated: 2021/12/02 08:18:27 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char *av[], char *env[])
{
	if(ac > 1)
	{
		char *full_path;
		char *mini_path;
	
		full_path = get_path(env);
		if(!full_path)
			return (1);
		mini_path = check_if_access(full_path, av[1]);
		if(!mini_path)
			printf("cmd not find :(\n");
		else
			printf("{%s}\n", mini_path);
	}
	return (0);
}