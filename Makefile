# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 01:38:09 by bel-oirg          #+#    #+#              #
#    Updated: 2024/03/28 03:46:08 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror -pthread# -fsanitize=thread

RM = rm -rf

SRCS = 	main.c philo_utils.c utils.c

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