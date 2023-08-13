# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 20:44:55 by htouil            #+#    #+#              #
#    Updated: 2023/08/11 16:02:57 by htouil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= philo.c philo_utils.c \
			libft/ft_bzero.c libft/ft_atoi.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

%.c: %.c
		$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(FLAGS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY	= all clean fclean re
		