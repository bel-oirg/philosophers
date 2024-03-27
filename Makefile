# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 01:38:09 by bel-oirg          #+#    #+#              #
#    Updated: 2024/03/27 02:11:41 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo  

CFLAGS = -Wall -Wextra -Werror -pthread# -fsanitize=thread -g

RM = rm -rf

SRCS = 	main.c philo_utils.c utils.c init.c checkers.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS) philo.h
	cc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME) philo.h

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJS)

re : fclean all

.PHONY: all clean fclean re