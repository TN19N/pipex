# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 07:23:30 by mannouao          #+#    #+#              #
#    Updated: 2021/12/02 08:23:21 by mannouao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = check_if_access.c\
		ft_split.c\
		ft_strjoin.c\
		ft_strlen.c\
		get_path.c\
		pipex.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -f $(NAME)

re : clean all