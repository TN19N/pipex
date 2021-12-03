# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 17:20:35 by mannouao          #+#    #+#              #
#    Updated: 2021/12/03 11:24:35 by mannouao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = ft_split.c\
		ft_strjoin.c\
		ft_strlen.c\
		get_path.c\
		pipex.c

OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all