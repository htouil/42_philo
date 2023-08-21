# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 20:44:55 by htouil            #+#    #+#              #
#    Updated: 2023/08/21 17:38:29 by htouil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= philo.c philo_utils.c \
			ft_bzero.c ft_atoi.c \

OBJS	= $(SRCS:.c=.o)

CC		= cc

FLAGS	= -Wall -Wextra -Werror -fsanitize=thread -g -pthread

all: $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(FLAGS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY	= all clean fclean re
		