# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htouil <htouil@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 20:44:55 by htouil            #+#    #+#              #
#    Updated: 2023/08/15 15:36:15 by htouil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= philo.c philo_utils.c \
			libft/ft_bzero.c libft/ft_atoi.c \
			ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_putstr.c \
			ft_printf/ft_putnbr.c ft_printf/ft_putnbruns.c ft_printf/ft_puthexlow.c \
			ft_printf/ft_puthexhigh.c ft_printf/ft_putvoid.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

FLAGS	= -Wall -Wextra -Werror -fsanitize=thread -g -O2 -pthread

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
		